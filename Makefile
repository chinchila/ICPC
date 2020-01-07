LATEX=latex
BIBTEX=bibtex
PDFTEX=pdflatex
FILE=notebook

all: comp

run: all
	gio open $(FILE).pdf

comp:
	python gen.py
	$(MAKE) clean

clean:
	rm -f $(FILE).aux $(FILE).log  $(FILE).spl $(FILE).bbl $(FILE).blg $(FILE).brf $(FILE).dvi $(FILE).idx $(FILE).out* $(FILE).toc $(FILE).fls $(FILE).fdb* contents.tex

