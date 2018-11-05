# ti83pce-Compiler
A simple compiler for ti83pce


## Introduction :

This software compile the *"ti83pce"* code into a `.8xp`, file which is executable by a *Texas Instruments 83 Premium CE calculator*, the progrtam should be executed by using the `Asm()` command.


## Running instructions :

something


## Language description :

Is an imperative oriented language

### Basic types

| Type | Description |
|-|-|
| byte | 8-bits unsigned value |
| sbyte | 8-bits signed value |
| word | 16-bits unsigned value |
| sword | 16-bits signed value |
| dword | 32-bits unsiged value |
| sdword | 32-bits signed value |
| qword | 64-bits unsiged value |
| sqword | 64-bits signed value |
| float | 32-bits floating-point value with base is 2 <br> 1-bit for sign, 8 for exponent  and 23 for significand |
| double | 64-bits floating-point value with base is 2 <br> 1-bit for sign, 11 for exponent  and 52 for significand |

## Language transcription

### Basics types declaration

#### Without value

Declaration without value are always like `type name;`.

| Type | Assembly Code |
|-|-|
| byte | `var_byte_name: .db 0 ` |
| sbyte | `var_sbyte_name: .db 0` |
| word | `var_word_name: .dw 0` |
| sword | `var_sword_name: .dw 0` |
| dword | `var_dword_name_1: .dw 0` <br> `var_dword_name_0: .dw 0` |
| sdword | `var_sdword_name_1: .dw 0` <br> `var_sdword_name_0: .dw 0` |
| qword | `var_qword_name_3: .dw 0` <br> `var_dword_name_2: .dw 0` <br> `var_dword_name_1: .dw 0` <br> `var_dword_name_0: .dw 0` |
| float | `var_float_name_1: .dw 0` <br> `var_float_name_0: .dw 0` |
| double | `var_double_name_3: .dw 0` <br> `var_double_name_2: .dw 0` <br> `var_double_name_1: .dw 0` <br> `var_double_name_0: .dw 0` |

#### With value

##### If value was an constant

Declaration with constant value are always like `type name = value;`.
The differents words of value are calculated by a function.

| Type | Assembly Code |
|-|-|
| byte | `var_byte_name: .db value` |
| sbyte | `var_sbyte_name: .db value` |
| word | `var_word_name: .dw value` |
| sword | `var_sword_name: .dw value` |
| dword | `var_dword_name_1: .dw <high word of value>` <br> `var_dword_name_0: .dw <low word of value>` |
| sdword | `var_sdword_name_1: .dw <high word of value>` <br> `var_sdword_name_0: .dw <low word of value>` |
| qword | `var_qword_name_3: .dw <high word of value>` <br> `var_dword_name_2: .dw <medium high word of value>` <br> `var_dword_name_1: .dw <medium low word of value>` <br> `var_dword_name_0: .dw <low word of value>` |
| float | `var_float_name_1: .dw 0` <br> `var_float_name_0: .dw 0` |
| double | `var_double_name_3: .dw 0` <br> `var_double_name_2: .dw 0` <br> `var_double_name_1: .dw 0` <br> `var_double_name_0: .dw 0` |
