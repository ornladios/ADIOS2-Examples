# Documentation for ADIOS2-Examples

# Generate html with Sphinx

This guide is hosted in readthedocs: https://adios2-examples.readthedocs.io/en/latest/

To generate the guide under docs/build/html format from the Sphinx source files:

```bash
$ cd ADIOS2-Examples/docs
docs$ python3 -m venv .
docs$ . bin/activate
docs$ pip3 install -r requirements.txt
docs$ make html
```
