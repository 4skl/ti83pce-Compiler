# ti83pce-Compiler
A simple compiler for ti83pce


## Introduction :

This software compile the *"ti83pce"* code into a `.8xp`, file which is executable by a *Texas Instruments 83 Premium CE calculator*, the progrtam should be executed by using the `Asm()` command.

## Development status :

Basics is actualy not finished, using of byte and word is active but arithmetics not ok.
Basic development is not finished, so, this readme is not contractual.

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
| sqword | `var_qword_name_3: .dw 0` <br> `var_dword_name_2: .dw 0` <br> `var_dword_name_1: .dw 0` <br> `var_dword_name_0: .dw 0` |
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
| sqword | `var_qword_name_3: .dw <high word of value>` <br> `var_dword_name_2: .dw <medium high word of value>` <br> `var_dword_name_1: .dw <medium low word of value>` <br> `var_dword_name_0: .dw <low word of value>` |
| float | `var_float_name_1: .dw 0` <br> `var_float_name_0: .dw 0` |
| double | `var_double_name_3: .dw 0` <br> `var_double_name_2: .dw 0` <br> `var_double_name_1: .dw 0` <br> `var_double_name_0: .dw 0` |

### Basics functions declaration

#### Addition

To add a to b and store it in c use `c = a + b`.

| Type | Assembly Code |
|-|-|
| byte | `ld a, (var_byte_a)` <br> `ld b, (var_byte_b) ` <br> `add a,b` <br> `ld (var_byte_c), a` |
| sbyte | `ld a, (var_byte_a)` <br> `ld b, (var_byte_b) ` <br> `add a,b` <br> `ld (var_byte_c), a` |
| word | `ld hl, (var_byte_a)` <br> `ld bc, (var_byte_b) ` <br> `add hl,bc` <br> `ld (var_byte_c), hl` |
| sword | `ld hl, (var_byte_a)` <br> `ld bc, (var_byte_b) ` <br> `add hl,bc` <br> `ld (var_byte_c), hl` |
| dword | `ld hl, (var_dword_a_0)` <br> `ld bc, (var_dword_b_0) ` <br> `add hl,bc` <br> `ld (var_dword_c_0), hl` <br> `ld hl, (var_dword_a_1)` <br> `ld bc, (var_dword_b_1) ` <br> `adc hl,bc` <br> `ld (var_dword_c_1), hl` |
| sdword | `ld hl, (var_dword_a_0)` <br> `ld bc, (var_dword_b_0) ` <br> `add hl,bc` <br> `ld (var_dword_c_0), hl` <br> `ld hl, (var_dword_a_1)` <br> `ld bc, (var_dword_b_1) ` <br> `adc hl,bc` <br> `ld (var_dword_c_1), hl` |
| qword | `ld hl, (var_dword_a_0)` <br> `ld bc, (var_dword_b_0) ` <br> `add hl,bc` <br> `ld (var_dword_c_0), hl` <br> `ld hl, (var_dword_a_1)` <br> `ld bc, (var_dword_b_1) ` <br> `adc hl,bc` <br> `ld (var_dword_c_1), hl` <br> `ld hl, (var_dword_a_2)` <br> `ld bc, (var_dword_b_2) ` <br> `adc hl,bc` <br> `ld (var_dword_c_2), hl` <br> `ld hl, (var_dword_a_3)` <br> `ld bc, (var_dword_b_3) ` <br> `adc hl,bc` <br> `ld (var_dword_c_3), hl` |
| float |  |
| double |  |


## Post Scriptum

I am a 17 year old french computer enthusiast and I suppose my English is not perfect (and apologise for that), my computer skills too, but I'm motivated and if I make this project is mostly for increasing my knowledge.

The idea of this project is coming from the first idea to make a game for my calculator in assembly, but I realized quickly that in assembly need so much instruction for making little things and that is boring for me. So at this point I have understood why compilers and upper level languages exist, so I decided to make my own.
