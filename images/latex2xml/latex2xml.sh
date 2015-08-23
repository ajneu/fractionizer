#!/bin/sh

## http://www.albany.edu/~hammond/demos/Html5/arXiv/lxmlexamples.html

## sudo apt-get install latexml
## sudo apt-get instal xmlstarlet    # used below to remove the footer


pname=`basename $0`
if [ "$#" != "1" ] ; then
    echo "Usage:    ${pname}  stem-name"
    exit 1
fi
stem="$1"
if [ ! \( -f "${stem}.tex" \) ] ; then
    echo "${pname}: Cannot find ${stem}.tex"
    exit 2
fi
latexml "--destination=${stem}.xml" "${stem}.tex"
if [ "$?" != "0" ] ; then
    echo "${pname}: latexml did not finish cleanly on ${stem}.tex"
    exit 3
fi
if [ ! \( -f "${stem}.xml" \) ] ; then
    echo "${pname}: Cannot find latexml output file ${stem}.xml"
    exit 4
fi
latexmlpost --format=html5 "--destination=${stem}.html" --presentationmathml "${stem}.xml"
if [ "$?" != "0" ] ; then
    echo "${pname}: latexmlpost did not finish cleanly on ${stem}.xml"
fi


## remove footer
cat "${stem}.html" | xmlstarlet -q fo --noindent --html --omit-decl go.html | xmlstarlet ed -O -P -d "/html/body/div/footer"  > "${stem}.html2"
mv "${stem}.html2" "${stem}.html"
