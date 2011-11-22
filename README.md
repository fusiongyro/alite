# alite - a lightweight procedural language

by Daniel Lyons <fusion@storytotell.org>

## Introduction

Alite is a very lightweight procedural language with emphasis on
Unicode. At the moment it is about as powerful as an integer `bc`. I
intend to draw on the ALGOL 60 reference to flesh out the language.

## Syntax Reference

Basic math operators: + - × ÷ ↑

Assignment: ← :=

You may use Unicode superscripts to indicate exponents as well as
Unicode subscripts to indicate base (not completely implemented yet).

## Sample session

    6×3+144÷12
    6 × 3 + 144 ÷ 12 = 30
    
    7↑3
    7³ = 343
    
    16⁵
    16⁵ = 1048576
    
    άλφα ← (b ← 2^3) + 4*2
    άλφα ← (b ← 2³) + 4 × 2 = 16
    
    άλφα^14
    άλφα¹⁴ = -2147483648
    
    b
    b = 8
    
    a ← 4 ↑ (b ← 7)
    a ← 4 ↑ (b ← 7) = 16384
    
    b
    b = 7
    