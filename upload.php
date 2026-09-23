<?php
/**
 * Secure G-Code File Upload & Analysis Handler
 *
 * Processes uploaded G-code files, enforces strict extension and filename sanitization,
 * protects against path traversal and command injection, and dispatches to the C++ parser.
 */

// Configure upload target directory
$uploadDir = __DIR__ . DIRECTORY_SEPARATOR . 'Files' . DIRECTORY_SEPARATOR;
if (!is_dir($uploadDir)) {
    mkdir($uploadDir, 0755, true);
}

// Configurable binary parser path via environment variable with fallback
$binaryPath = getenv('FILETEST_BIN_PATH') ?: (__DIR__ . DIRECTORY_SEPARATOR . 'filetest');
if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN' && !str_ends_with(strtolower($binaryPath), '.exe')) {
    if (file_exists($binaryPath . '.exe')) {
        $binaryPath .= '.exe';
    }
}

// Whitelist permitted file extensions
$allowedExtensions = ['gcode', 'txt'];

$messages = [];

if (!empty($_FILES)) {
    foreach ($_FILES as $fileKey => $file) {
        if (!isset($file['error']) || is_array($file['error'])) {
            $messages[] = "Invalid upload parameter structure.";
            continue;
        }

        if ($file['error'] !== UPLOAD_ERR_OK) {
            $messages[] = "Upload failed with error code: " . htmlspecialchars((string)$file['error'], ENT_QUOTES, 'UTF-8');
            continue;
        }

        // Sanitize original filename and strip path traversal characters
        $rawFilename = basename($file['name']);
        $extension = strtolower(pathinfo($rawFilename, PATHINFO_EXTENSION));

        // Strict extension validation
        if (!in_array($extension, $allowedExtensions, true)) {
            $messages[] = "File <b>" . htmlspecialchars($rawFilename, ENT_QUOTES, 'UTF-8') . "</b> rejected. Allowed extensions: ." . implode(', .', $allowedExtensions);
            continue;
        }

        // Clean filename to alphanumeric characters, underscores, hyphens, and single dots
        $safeBase = preg_replace('/[^a-zA-Z0-9_-]/', '_', pathinfo($rawFilename, PATHINFO_FILENAME));
        $sanitizedFilename = $safeBase . '.' . $extension;
        $destination = $uploadDir . $sanitizedFilename;

        // Move uploaded file to target directory safely
        if (!move_uploaded_file($file['tmp_name'], $destination)) {
            $messages[] = "Failed to store uploaded file: " . htmlspecialchars($rawFilename, ENT_QUOTES, 'UTF-8');
            continue;
        }

        // Execute C++ analysis tool with strictly escaped shell arguments
        if (file_exists($binaryPath)) {
            $command = escapeshellcmd($binaryPath) . ' ' . escapeshellarg($destination);
            $output = [];
            $returnCode = 0;
            exec($command, $output, $returnCode);

            $parsedOutput = htmlspecialchars(implode("\n", $output), ENT_QUOTES, 'UTF-8');
            $messages[] = "-> File <b>" . htmlspecialchars($sanitizedFilename, ENT_QUOTES, 'UTF-8') . "</b> analyzed successfully.<br><pre>{$parsedOutput}</pre>";
        } else {
            $messages[] = "-> File <b>" . htmlspecialchars($sanitizedFilename, ENT_QUOTES, 'UTF-8') . "</b> stored. (Parser binary not found at " . htmlspecialchars($binaryPath, ENT_QUOTES, 'UTF-8') . ").";
        }
    }
}

echo implode('<br>', $messages);