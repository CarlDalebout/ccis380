
pdf:
	pdflatex --shell-escape main.tex
	pdflatex --shell-escape main.tex
	make cleantmp

view:
	xdg-open main.pdf

v:
	xdg-open main.pdf
cleantmp:
	rm -rf abc.outut
	rm -rf 'main.log' 
	rm -rf 'main.aux'
	rm -rf 'main.toc'
	rm -rf 'main.out'
	rm -rf 'main.idx'
	rm -rf 'main.ilg'
	rm -rf 'texput.log'
	rm -rf 'shEsc.tmp'
	rm -rf 'main.vrb'
	rm -rf 'main.snm'
	rm -rf 'main.nav'
	rm -rf 'abc.output'

clean:
	rm -rf 'main.pdf'
	make cleantmp
        
c:
	rm -rf 'main.pdf'
	make cleantmp
