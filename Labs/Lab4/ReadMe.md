# STM32 Performance Measurements

This table provides the timing measurements for various operations on the STM32F103RB microcontroller, tested with different compiler optimization levels using STM32CubeIDE.

| Operation              | No Optimization (-O0) | Optimize for debug(-Og)|Optimize (-O1) | Optimize More (-O2) | Optimize Most (-O3) | Optimize for Size (-Os) | Fastest (-Ofast) | 
|------------------------|--|-- |--|--|--|--|--| 
| **32-bit Addition**    |54 |38 |38 |42 |40 |46 |40|
| **64-bit Addition**    |64 |42 |42 |46 |44 |48 |44|
| **32-bit Multiplication** |54 |38 |37 |44 |40 |46 |40|
| **64-bit Multiplication** |70 |42 |42 |48 |44 |48 |44|
| **32-bit Division**    |63 |46 |46 |46 |44 |48 |44|
| **64-bit Division**    |202 |54 |58 |52 |50 |52 |50|
| **8-byte Struct Copy** |56 |42 |44 |48 |44 |50 |44|
| **128-byte Struct Copy** |1230 |1211 |1211 |1217 |1213 |1218 |1213|
| **1024-byte Struct Copy** |127 |112 |105 |110 |106 |110 |106|


The following observations can be made from the table above:
- **Addition & Multiplication**: Minor improvements with higher optimizations (`-O1` to `-Ofast`), around 20-30% faster.
- **Division (32-bit & 64-bit)**: Noticeable speedup, especially for 64-bit, with `-O3` and `-Ofast`.
- **Struct Copy (8-byte)**: Modest gains across levels, stabilizes with `-O2` and above.
- **Struct Copy (128-byte & 1024-byte)**: Significant time reduction at `-O1` and higher, especially for large structs.
- **Overall** : Higher optimazation levels (`-O3` and `-Ofast`) provide the best performance improvements for most operations.