#pragma once

struct FileNotOpen
{
public:
  const char *fileName;

public:
  FileNotOpen(const char *rhsFileName) : fileName(rhsFileName)
  {
  }

public:
  void what() const
  {
    printf("Failed to open file %s.\n", fileName);
  }
};

struct InvalidFileFormat
{
public:
  const int maxRows;
  const int maxCols;

public:
  InvalidFileFormat(const int rhsMR,
                    const int rhsMC) : maxRows(rhsMR),
                                       maxCols(rhsMC)
  {
  }

public:
  void what() const
  {
    printf("File should be [1;%d] rows by [1;%d] cols "
           "including end of line specifiers on each line.\n",
           maxRows, maxCols);
  }
};