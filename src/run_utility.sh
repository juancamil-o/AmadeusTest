#!/bin/bash

# IN and OUT files
JSON_FILE="employees.json"
XML_FILE="employees.xml"
OUTPUT_FILE="output.txt"
LOG_FILE="run.log"
EXECUTABLE="./main" 

# Cleaning logs
echo "Executing script..." > "$LOG_FILE"

# Check if files exists
INPUT_FILES=()
if [[ -f "$JSON_FILE" ]]; then
    INPUT_FILES+=("$JSON_FILE")
fi
if [[ -f "$XML_FILE" ]]; then
    INPUT_FILES+=("$XML_FILE")
fi

# if not files, rise error
if [[ ${#INPUT_FILES[@]} -eq 0 ]]; then
    echo "Error: Neither JSON nor XML files has been found." | tee -a "$LOG_FILE"
    exit 1
fi

echo "Processing files: ${INPUT_FILES[*]}" | tee -a "$LOG_FILE"

# execute 
"$EXECUTABLE" "${INPUT_FILES[@]}" >> "$OUTPUT_FILE" 2>> "$LOG_FILE"

# check if execution was sucessfull
if [[ $? -ne 0 ]]; then
    echo "Error while processing files. Check logs in '$LOG_FILE'" | tee -a "$LOG_FILE"
fi

echo "Execution completed. Output saved in '$OUTPUT_FILE'" | tee -a "$LOG_FILE"
