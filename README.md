# Bin2XML

You are asked to develop a command line tool to convert a binary file to
XML format. All coding must be in C programming language. 

# Requirements

* GNU Compiler Collection (gcc)

# Example One Record Outputs

```
<records>
    <row id=”1”>
        <name>James </name>
        <surname>Butt</surname>
        <gender>M</gender>
        <email>jbutt@gmail.com</email>
        <phone_number>504-845-1427</phone_number>
        <address>7 W Cerritos Ave #54</address>
        <level_of_education>MSc</level_of_education>
        <income_level bigEnd=1798766592>14187</income_level>
        <expenditure bigEnd=3758686208>2528</expenditure>
        <currency_unit>$</currency_unit>
        <currentMood> </currentMood>
        <height>1.33</height>
        <weight>68</weight>
    </row>
    ...
</records>
```

## installation
```
$ Bin2XML % gcc main.c -o Bin2XML
$ Bin2XML % ./Bin2XML <records-source> <output-destination>
```
## todo list

|macro|description|status|
|-|-|:-:|
|`getting terminal arguments`|Program should be give CLI arguments|:heavy_check_mark:|
|`another type output`|Program should be creatable different outputs (pdf,csv)|:soon:|

