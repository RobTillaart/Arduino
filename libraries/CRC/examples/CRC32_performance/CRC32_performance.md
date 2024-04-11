Test Lorum ipsum (868 bytes).
2023-06-05 (intermediate 1.0.0)


## Arduino UNO (16 MHz)

### Compile size

| Version | Size / vars |
|:-------:|:------------|
|  0.3.3  | 4036 / 1190 |
|  1.0.0  | 3972 / 1194 |
|  Diff   |  -64 / 4    | 



### Runtimes


|   algo    |  output 0.3.3  |  output 1.0.0  | time 0.3.3 | time 1.0.0 | delta % | notes |
|:---------:|:--------------:|:--------------:|:----------:|:----------:|:-------:|:------|
|   CRC32   |  36ED2953      |  5E22D36F      |    7468    |    8236    |  +10%   |
|   CRC32   |  BB768E7C      |  5E22D36F      |    8252    |    7764    |  -06%   |


- Output differs in 0.3.3 and from 1.0.0. 
 - not all flags set in 0.3.3 mode, default 1.0.0 differs (ignores flags).
- https://crccalc.com/ ==>  5E22D36F
- timing is +- roughly comparable.


## ESP32 (240 MHz)

### Compile size

- less interesting as sufficient RAM.


### Runtimes

| algo  | output 0.3.3  |  output 1.0.0  | time 0.3.3 | time 1.0.0 | delta % | notes |
|:-----:|:-------------:|:--------------:|:----------:|:----------:|:-------:|:------|          
| CRC32 |  36ED2953     |  5E22D36F      |    621     |     598    |  -04%   |
| CRC32 |  BB768E7C     |  5E22D36F      |    705     |     583    |  -20%   |


- Output is identical to UNO test. 
- Timing is faster in 1.0.0.



