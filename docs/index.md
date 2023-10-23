# Vulcan  Documentation

This is the start of the Vulcan Documentation

For help editing the documentation visit [mkdocs.org](https://www.mkdocs.org). To generate the docs locally `mkdocs serve`
and point the browser to [127.0.0.1.8000](http://127.0.0.1:8000)
It will be link to readdocs in future 


## Folder layout

    src/          # source code
    InitializationData/     # initialization
    PythonDataAnalysis/     # Python Analysis
    wrk/          # work directory, results will be there
    docs/         # documentation folder
    tst/          # test folder
    mkdocs.yml    # The configuration file.
    README        # Usual README file



## Pre-requisites

1. **C++ compiler** 
Tested with Apple clang version 13.1.6 and gcc version 12.2.0
(need C++17 standard)

2. **GNU Makefile** 
It will usually be installed by default in most systems (Mac OS/Linux). It may not needed if compilation with VisualStudio or similar, but it is recomended

3. **Python**
Use of [jupyter books](https://jupyter.org)  to analyse and plot the data.

4. **Documentation**
Install with  `pip install mkdocs` to see the doumentation locally. Not needed to run the code or edit the documentation files.


## Installation

Using latest version on the master branch

* `gh repo clone ImperialCollegeLondon/Vulcan` - requites installing GitHub CLI


## Initialization
