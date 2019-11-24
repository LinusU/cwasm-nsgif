# GIF

GIF decoding for Node.js, using [Libnsgif][Libnsgif] compiled to [WebAssembly][WebAssembly].

[Libnsgif]: https://www.netsurf-browser.org/projects/libnsgif/
[WebAssembly]: https://webassembly.org

## Installation

```sh
npm install --save @cwasm/nsgif
```

## Usage

```js
const fs = require('fs')
const nsgif = require('@cwasm/nsgif')

const source = fs.readFileSync('image.gif')
const image = nsgif.decode(source)

console.log(image)
// { width: 128,
//   height: 128,
//   data:
//    Uint8ClampedArray [ ... ] }
```

## API

### `decode(source)`

- `source` ([`Uint8Array`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Uint8Array), required) - The GIF data
- returns [`ImageData`](https://developer.mozilla.org/en-US/docs/Web/API/ImageData) - Decoded width, height and pixel data
