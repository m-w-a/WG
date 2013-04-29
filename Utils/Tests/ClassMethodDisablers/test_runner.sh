#!/bin/sh

testFiles=(
  CopyAssignmentUnitTest.cc 
  CopyCtorUnitTest.cc 
  DefaultCtorUnitTest.cc 
  DeleteArrayNoThrowUnitTest.cc 
  DeleteArrayUnitTest.cc 
  DeleteNoThrowUnitTest.cc 
  DeleteUnitTest.cc 
  NewArrayNoThrowUnitTest.cc
  NewArrayUnitTest.cc 
  NewNoThrowUnitTest.cc 
  NewUnitTest.cc)

didAllTestsPass=true
  
function runTests()
{
  for file in "${testFiles[@]}"
  do
    result="$(g++ -I/home/HPC/Working/Projects/cpp "${file}" >& /dev/null || echo "SUCCESS")"

    if [ "${result}" != SUCCESS ]
    then
      echo "${file} ... test failed."
      didAllTestsPass=false
    fi
    
  done
}

function displayResults()
{
  if [ "${didAllTestsPass}" = true ]
  then
    echo "ClassMethodDisablers ... all unit tests passed."
    exit 0
  else
    echo "ClassMethodDisablers ... some unit tests failed."
    exit -1;
  fi
}

runTests
displayResults
