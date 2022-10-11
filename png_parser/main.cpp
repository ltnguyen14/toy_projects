#include <string.h>

#include "fstream"
#include "stdio.h"
#include "typedefs.hpp"

void reverseBytes(byte *data, s32 size);
void ParseHeaderInfo(byte *data);

int main() {
  const byte HEADER_BYTES[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
  byte headerBytes[8];
  FILE *f = fopen("spiderman.png", "rb");

// Raw data
#if 0
  byte data;
  while (fread(&data, 1, 1, f) != 0) {
    printf("%02X ", data);
  }
  printf("\n");
  fseek(f, 0, SEEK_SET);
#endif

  // Signature
  fread(headerBytes, 8, 1, f);
  bool headerCheck = true;
  printf("Header bytes read: ");
  for (s32 i = 0; i < 8; i++) {
    printf("%02X ", headerBytes[i]);
    if (headerBytes[i] != HEADER_BYTES[i]) {
      headerCheck = false;
    }
  }
  printf("\n");

  if (headerCheck) {
    printf("Signature is correct.\n\n");
  } else {
    printf("Signature is INCORRECT.\n");
    return -1;
  }

  // Chunks
  u32 chunkLength;
  byte chunkType[5];
  chunkType[4] = '\0';
  byte crc[4];

  printf("=============\n");
  while (strcmp((const char *)chunkType, "IEND") != 0) {
    fread(&chunkLength, 4, 1, f);
    reverseBytes((byte *)&chunkLength, 4);

    fread(chunkType, 4, 1, f);

    byte *data = (byte *)malloc(chunkLength);
    fread(data, chunkLength, 1, f);

    fread(&crc, 4, 1, f);

    printf("Chunk Type: %s\n", chunkType);
    if (chunkType[0] <= 'Z') {
      printf("Property: Critical.\n");
    } else if (chunkType[0] >= 'a') {
      printf("Property: Ancillary.\n");
    }

    if (chunkType[1] <= 'Z') {
      printf("Property: Public.\n");
    } else if (chunkType[0] >= 'a') {
      printf("Property: Private.\n");
    }

    if (chunkType[3] <= 'Z') {
      printf("Property: Unsafe to copy.\n");
    } else if (chunkType[0] >= 'a') {
      printf("Property: Safe to copy.\n");
    }

    printf("Chunk Length: %u\n", chunkLength);

    if (strcmp((const char *)chunkType, "IHDR") == 0) {
      ParseHeaderInfo(data);
    }

    printf("=============\n");
  }
}

// This assumes data is 13 bytes.
void ParseHeaderInfo(byte *data) {
  /**
   Width:              4 bytes
   Height:             4 bytes
   Bit depth:          1 byte
   Color type:         1 byte
   Compression method: 1 byte
   Filter method:      1 byte
   Interlace method:   1 byte
   **/

  byte *ptr = data;
  reverseBytes(ptr, 4);
  s32 width = *(s32*)ptr;
  ptr += 4;
  reverseBytes(ptr, 4);
  s32 height = *(s32*)ptr;
  ptr += 4;
  byte bitDepth = *ptr; 
  ptr++;
  byte colorType = *ptr; 
  ptr++;
  byte compressionMethod = *ptr; 
  ptr++;
  byte filterMethod = *ptr; 
  ptr++;
  byte interlaceMethod = *ptr; 

  printf("Width: %d\n", width);
  printf("Height: %d\n", height);
  printf("Bit depth: %d\n", bitDepth);
  printf("Color type: %d\n", colorType);
  printf("Compression method: %d\n", compressionMethod);
  printf("Filter method: %d\n", filterMethod);
  printf("Interlace method: %d\n", interlaceMethod);
}

void reverseBytes(byte *data, s32 byteCount) {
  byte temp;
  for (s32 i = 0; i < byteCount / 2; i++) {
    temp = data[i];
    data[i] = data[byteCount - i - 1];
    data[byteCount - i - 1] = temp;
  }
}
