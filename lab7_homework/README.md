### Updated `README.md` to Reflect Requirements

```markdown # String Processor with Pipes and Forks

This program is a C application that demonstrates inter-process communication
using pipes and forks. It processes the content of a file, reverses the string,
and categorizes characters based on specific requirements.

## Program Requirements

1. **Input**:
   - The program accepts one command-line argument representing the file path.
   - The file contains a string to be processed.

2. **Parent Process**:
   - Reads the content of the file.
   - Reverses the content.
   - Sends the reversed content to the child process through a pipe.

3. **Child Process**:
   - Receives the reversed string from the parent.
   - Processes the string by:
     - Counting and extracting digits, uppercase letters, lowercase letters,
       and "other" characters.
   - Sends the processed information back to the parent in the format: ``` <int
     N><N chars><int M><M chars><int L><L chars><K chars> ```

   - Example of the format:
     - `N` is the count of digits followed by the digits.
     - `M` is the count of uppercase letters followed by the letters.
     - `L` is the count of lowercase letters followed by the letters.
     - `K chars` represents the remaining characters.

4. **Output**:
   - The parent prints:
     - The initial content of the file.
     - The reversed content sent to the child.
     - The processed content received from the child.

### Example

Given a file `input.txt` containing: ``` World News America, 21/11/2024 ```

#### Process Flow:

1. **Parent Process** sends the reversed content: ``` 4202/11/12,aciremA sweN
dlroW ```

2. **Child Process** sends back: ```
8420211123ANW13aciremswedlro//,<space><space> ```

3. **Output**: ``` Initial File Content: World News America, 21/11/2024 Parent
Sending (Reversed): 4202/11/12,aciremA sweN dlroW

   Child Received (Reversed): 4202/11/12,aciremA sweN dlroW Parent Received
   from Child (Processed): 8420211123ANW13aciremswedlro//,<space><space> ```

## Usage

### Compilation

Use the provided `Makefile`: ```bash make ```

### Running the Program

Provide a text file (e.g., `input.txt`) containing the string to be processed:
```bash ./string_processor input.txt ```

### Cleaning Up

To remove the compiled files, run: ```bash make clean ```
