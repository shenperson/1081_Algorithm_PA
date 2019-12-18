#! /bin/bash
echo "cb..."
./cb public_cases/public_case_"$1".in output/"$1".out
echo "check..."
./pa3_checker public_cases/public_case_"$1".in output/"$1".out
