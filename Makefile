SHELL = /bin/sh

.PHONY: publish
publish:
	python3 setup.py sdist --formats=bztar upload
	rm -rf build/ dic32.egg-info/ dist/
	git add -A
	git commit -m "Published `python3 setup.py --version`"
	git tag `python3 setup.py --version`
	git push
	git push --tags
