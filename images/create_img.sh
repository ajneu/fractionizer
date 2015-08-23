#!/usr/bin/env bash

# sudo apt-get install texlive
# sudo apt-get install texlive-latex-extra  # for latex package standalone
# sudo apt-get install pdf2svg

files_array=(
cont_frac
equation
example_frac
reciprocal
vector_example
vector
vectors
w_i
whole
x_i
x_i1
x_j
)

for i in "${files_array[@]}"
do
    pdflatex -shell-escape "$i".tex
    rm "$i.aux" "$i.log" "$i.pdf"
done
