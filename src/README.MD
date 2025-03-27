# Developer Test AMADEUS

###### This utility processes employee data from JSON and XML files, calculates salary statistics, outputs results to a text file and includes Unix shell scripts for automation.

## Compilation

### Ensure you have a C++11 compatible compiler installed. To compile the project, run:

 g++ -std=c++11 -o main main.cpp json_parser.cpp xml_parser.cpp

## Execution

### To process employee data from both JSON and XML files, use the provided shell script and provide permissions for the execution:
 chmod +x run_utility.sh

 ./run_utility.sh

## Running the executable manually:

### You can also run the utility manually with a specific input file:

 ./main employees.json
 ./main employees.xml

## Output

 The results, including average salary, highest-paid employee details, and sorted employee lists, will be saved in an output text file.

## Logs

Execution logs, including errors and processed file details, are recorded in a log file for debugging purposes.

## Testing

Ensure the input files employees.json and employees.xml are present in the expected format before running the utility.


# Note

FYI The document that I followed for the development is located in this same folder