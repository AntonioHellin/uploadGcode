# gcode-upload-analyzer

A lightweight web interface and C++ backend service for parsing, analyzing, and validating 3D printer G-Code files.

## Project Overview

`gcode-upload-analyzer` combines a responsive browser frontend with a high-performance C++ parser to inspect 3D printing toolpaths. It calculates total layer counts, distinguishes between extrusion and non-extrusion movements, and computes maximum bounding-box dimensions (X, Y, Z axes) from uploaded G-code files.

## Features

- **G-Code Geometry Analysis**: Computes the exact bounding box (Max X, Max Y, Max Z) and total physical layer count.
- **Extrusion Profiling**: Tracks extrusion vs. non-extrusion movement commands (`G1` with and without `E` arguments).
- **Secure File Handling**: Implements strict extension whitelisting (`.gcode`, `.txt`), path traversal prevention, and shell argument escaping.
- **Modern Web Interface**: Responsive interface using HTTPS-secured CDN libraries and AJAX uploads.

## Prerequisites

- **Web Server**: Apache or Nginx with PHP 8.0+ installed and enabled.
- **PHP Extensions**: Standard `fileinfo` and file upload support (`file_uploads = On` in `php.ini`).
- **C++ Compiler**: GCC (g++ 10+), Clang (11+), or MSVC (Visual Studio 2019+).

## Installation / Build

1. Clone the repository into your web root (or local directory):
   ```bash
   git clone https://github.com/AntonioHellin/gcode-upload-analyzer.git
   cd gcode-upload-analyzer
   ```

2. Compile the C++ parsing binary:
   - On Linux / macOS:
     ```bash
     g++ -O2 -std=c++17 filetest.cpp -o filetest
     chmod +x filetest
     ```
   - On Windows:
     ```cmd
     cl /EHsc /std:c++17 filetest.cpp /Fe:filetest.exe
     ```

3. Ensure the upload storage directory exists with write permissions:
   ```bash
   mkdir -p Files
   chmod 755 Files
   ```

## Configuration & Environment Variables

The PHP handler can optionally be configured via environment variables:

| Variable | Default | Description |
| :--- | :--- | :--- |
| `FILETEST_BIN_PATH` | `./filetest` | Absolute path to the compiled C++ parser binary |

## Usage

### Web Interface

1. Start the PHP built-in web server for local development:
   ```bash
   php -S localhost:8000
   ```
2. Open your browser and navigate to `http://localhost:8000`.
3. Choose a `.gcode` file using the file selector and click **Start Analysis**.
4. The analysis report will appear directly on screen.

### CLI Direct Usage

You can also run the analysis utility directly from your command line:

```bash
./filetest Files/test.gcode
```

Example output:
```text
Number of extrusion movements: 432
Number of non-extrusion movements: 120
Number of layers in the 3D model: 85
Max X: 120.45
Max Y: 115.30
Max Z: 18.20
```

## License

This project is licensed under the [MIT License](LICENSE).
