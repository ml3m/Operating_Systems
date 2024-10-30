# Documentation: Directory Tree Copy Program

This documentation describes a C program designed to recursively copy a complete directory tree from a specified source path to a target destination. It preserves the structure and file types within the source directory, supporting various file types.

## Supported File Types

The program identifies and handles the following file types:

- **DT_REG**: Regular file (copied using `copy_file`)
- **DT_DIR**: Directory (copied recursively using `copy_entity`)
- **DT_LNK**: Symbolic link (copied using `copy_symlink`)

- **DT_FIFO**: FIFO (named pipe) – skipped, with a warning
- **DT_SOCK**: Socket – skipped, with a warning
- **DT_CHR**: Character device – skipped, with a warning
- **DT_BLK**: Block device – skipped, with a warning
- **DT_UNKNOWN**: Unknown type – skipped, with a warning

## Program Structure

### Functions

- **`copy_file`**: Copies regular files.
- **`copy_symlink`**: Copies symbolic links.
- **`copy_entity`**: Recursively handles directory contents and dispatches the appropriate function based on file type.

### Compilation

To compile the program, use:

```bash
gcc lab4_solve.C
```

## Usage

Run the program with two arguments: a source directory and a destination path. 

### Syntax

```bash
./a.out <source_directory> <destination_directory>
```

### Example

To copy `/source/path` into `/destination/path`, run:

```bash
./a.out /source/path /destination/path
```

## Notes

- **Error Handling**: If the source directory or files cannot be accessed, the program exits with an error message.
- **Destination Path**: The destination must not already exist to prevent overwriting.
- **Unsupported File Types**: For FIFOs, sockets, character devices, block devices, and unknown types, the program outputs a warning and skips these files.

