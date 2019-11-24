/* eslint-env mocha */

const assert = require('assert')
const fs = require('fs')

const ImageData = require('@canvas/image-data')
const lodepng = require('lodepng')

const nsgif = require('./')

const fixtures = ['waves', 'WFPC05']

describe('libnsgif', () => {
  for (const fixture of fixtures) {
    it(`decodes "${fixture}.gif"`, async () => {
      const referenceSource = fs.readFileSync(`fixtures/${fixture}_ref.png`)
      const reference = await lodepng.decode(referenceSource)

      const source = fs.readFileSync(`fixtures/${fixture}.gif`)
      const result = nsgif.decode(source)

      assert(result instanceof ImageData)
      assert.strictEqual(result.width, reference.width)
      assert.strictEqual(result.height, reference.height)
      assert.deepStrictEqual(result.data, reference.data)
    })
  }
})
