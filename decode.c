#include <stdlib.h>

#include "libnsgif.h"

#define BYTES_PER_PIXEL 4
#define MAX_IMAGE_BYTES (48 * 1024 * 1024)

static void *bitmap_create(int width, int height) {
  /* ensure a stupidly large bitmap is not created */
  if (((long long)width * (long long)height) > (MAX_IMAGE_BYTES/BYTES_PER_PIXEL)) {
    return NULL;
  }

  return calloc(width * height, BYTES_PER_PIXEL);
}

void bitmap_destroy(void *bitmap) {
  // The data is NOT freed here since we are passing it back and want it to live longer than the `gif_animation`
}

unsigned char *bitmap_get_buffer(void *bitmap) { return bitmap; }
static void bitmap_set_opaque(void *bitmap, bool opaque) {}
static bool bitmap_test_opaque(void *bitmap) { return false; }
static void bitmap_modified(void *bitmap) {}

gif_result decode_gif(unsigned char** out, unsigned* w, unsigned* h, uint8_t* in, size_t insize) {
  gif_bitmap_callback_vt bitmap_callbacks = {
    bitmap_create,
    bitmap_destroy,
    bitmap_get_buffer,
    bitmap_set_opaque,
    bitmap_test_opaque,
    bitmap_modified
  };

  gif_result code;
  gif_animation gif;

  /* create our gif animation */
  gif_create(&gif, &bitmap_callbacks);

  /* begin decoding */
  do {
    code = gif_initialise(&gif, insize, in);
  } while (code == GIF_WORKING);
  if (code != GIF_OK) goto cleanup;

  code = gif_decode_frame(&gif, 0);
  if (code != GIF_OK) goto cleanup;

  *out = gif.frame_image;
  *w = gif.width;
  *h = gif.height;

cleanup:
  if (code != GIF_OK) free(gif.frame_image);
  gif_finalise(&gif);
  return code;
}
