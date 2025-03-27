#!/bin/bash

# routes definition
JSON_FILE="./inputs/employees.json"
XML_FILE="./inputs/employees.xml"
OUTPUT_FILE="./outputs/output.txt"
LOG_FILE="./outputs/run.log"
EXECUTABLE="./main"

# create folders if doesn't exists
mkdir -p inputs outputs

# Cleaning files 
> "$OUTPUT_FILE"
> "$LOG_FILE"

# Execute program with JSON and XML files
echo "Processing files: $JSON_FILE $XML_FILE" | tee -a "$LOG_FILE"
"$EXECUTABLE" "$JSON_FILE" "$XML_FILE" > "$OUTPUT_FILE" 2>> "$LOG_FILE"

# check if sucessfull execution
if [[ $? -ne 0 ]]; then
    echo "Error while processing files. Check logs in '$LOG_FILE'" | tee -a "$LOG_FILE"
else
    echo "Execution completed. Output saved in '$OUTPUT_FILE'" | tee -a "$LOG_FILE"
fi
