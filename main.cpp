#include <string.h>

#include "fstream"
#include "stdio.h"
#include "typedefs.hpp"

void reverseBytes(byte *data, s32 size);

int main() {
  const byte HEADER_BYTES[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
  byte headerBytes[8];
  FILE *f = fopen("image.png", "rb");

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
    printf("Signature is correct.\n");
  } else {
    printf("Signature is INCORRECT.\n");
    return -1;
  }

  // Chunks
  u32 chunkLength;
  byte chunkType[5];
  chunkType[4] = '\0';
  byte crc[4];

  s32 test = 0;
  while(strcmp((const char*)chunkType, "IEND") != 0 && test < 10) {
    test++;
    fread(&chunkLength, 4, 1, f);
    reverseBytes((byte*)&chunkLength, 4);

    fread(chunkType, 4, 1, f);

    fseek(f, chunkLength, SEEK_CUR);

    fread(&crc, 4, 1, f);

    printf("Chunk Type: %s\n", chunkType);
    printf("Chunk Length: %u\n", chunkLength);

    printf("=============\n");

  }
}

void reverseBytes(byte *data, s32 byteCount) {
  byte temp;
  for (s32 i = 0; i < byteCount / 2; i++) {
    temp = data[i];
    data[i] = data[byteCount - i];
    data[byteCount - 1] = temp;
  }
}
