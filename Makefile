.PHONY: test

nsgif.wasm: Dockerfile decode.c
	docker build .
	sh -c 'docker run --rm -it $$(docker build -q .) | base64 -D > nsgif.wasm'

test: nsgif.wasm index.js test.js
	@node_modules/.bin/standard
	@node_modules/.bin/mocha
	@node_modules/.bin/ts-readme-generator --check
