#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <string.h>

#define kw 4
#define nb 4

using namespace std;

vector<vector<int>> Sbox = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};

vector<vector<int>> InvSbox = {
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};

// 平文s
vector<vector<int>> state = {
    {0x32, 0x43, 0xf6, 0xa8},
    {0x88, 0x5a, 0x30, 0x8d},
    {0x31, 0x31, 0x98, 0xa2},
    {0xe0, 0x37, 0x07, 0x34}};

// 暗号化鍵
vector<vector<int>> key = {
    {0x2b, 0x7e, 0x15, 0x16},
    {0x28, 0xae, 0xd2, 0xa6},
    {0xab, 0xf7, 0x15, 0x88},
    {0x09, 0xcf, 0x4f, 0x3c}};

// SubBytes関数：各バイトをS-Boxで置き換える
int SubBytes(vector<vector<int>> &state)
{
  int k, l;
  for (int i = 0; i < nb; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      k = state[i][j] / 16;
      l = state[i][j] % 16;
      state[i][j] = Sbox[k][l];
    }
  }
  return 0;
}
// 　 SubBytesと同じ操作
void InvSubBytes(vector<vector<int>> &encryptionState)
{
  int k, l;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      k = encryptionState[i][j] / 16;
      l = encryptionState[i][j] % 16;
      encryptionState[i][j] = InvSbox[k][l];
    }
  }
}
// AddRoundKey関数：平文と暗号化鍵をXorする
int AddRoundKey(vector<vector<int>> &state, vector<vector<int>> &key)
{
  int i, j;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      state[i][j] = state[i][j] ^ key[i][j];
    }
  }
  return 0;
}
// AddRoundKeyと全く同じ操作
void InvAddRoundKey(vector<vector<int>> &encryptionState, vector<vector<int>> &decryption)
{
  int i, j;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      encryptionState[i][j] = encryptionState[i][j] ^ decryption[i][j];
    }
  }
}
// ShiftRows関数：各行を左にシフトする
int ShiftRows(vector<vector<int>> &state)
{
  int i;
  vector<int> line1(4);
  vector<int> line2(4);
  vector<int> line3(4);
  vector<int> line4(4);
  for (i = 0; i < 4; i++)
  {
    line1[i] = state[i][0];
    line2[i] = state[i][1];
    line3[i] = state[i][2];
    line4[i] = state[i][3];
  }
  rotate(line2.begin(), line2.begin() + 1, line2.end());
  rotate(line3.begin(), line3.begin() + 2, line3.end());
  rotate(line4.begin(), line4.begin() + 3, line4.end());

  for (i = 0; i < 4; i++)
  {
    state[i][0] = line1[i];
    state[i][1] = line2[i];
    state[i][2] = line3[i];
    state[i][3] = line4[i];
  }
  return 0;
}
// shiftRowsと全く同じ操作
void InvShiftRows(vector<vector<int>> &encryptionState)
{
  int i;
  vector<int> line1(4);
  vector<int> line2(4);
  vector<int> line3(4);
  vector<int> line4(4);
  for (i = 0; i < 4; i++)
  {
    line1[i] = encryptionState[i][0];
    line2[i] = encryptionState[i][1];
    line3[i] = encryptionState[i][2];
    line4[i] = encryptionState[i][3];
  }
  rotate(line2.rbegin(), line2.rbegin() + 1, line2.rend());
  rotate(line3.rbegin(), line3.rbegin() + 2, line3.rend());
  rotate(line4.rbegin(), line4.rbegin() + 3, line4.rend());

  for (i = 0; i < 4; i++)
  {
    encryptionState[i][0] = line1[i];
    encryptionState[i][1] = line2[i];
    encryptionState[i][2] = line3[i];
    encryptionState[i][3] = line4[i];
  }
}
int xtime(unsigned char b)
{
  return (b << 1) ^ ((b & 0x80) ? 0x1b : 0x00);
}
int dot(int x, int y)
{
  unsigned char mask;
  unsigned char product = 0;

  for (mask = 0x01; mask; mask <<= 1)
  {
    if (y & mask)
    {
      product ^= x;
    }
    x = xtime(x);
  }
  return product;
}
// MixColums関数：列ミックス変換を適用する
int MixColumns(vector<vector<int>> &state)
{
  int i;
  vector<int> t(4);

  for (i = 0; i < 4; i++)
  {
    t[0] = dot(2, state[i][0]) ^ dot(3, state[i][1]) ^ state[i][2] ^ state[i][3];
    t[1] = state[i][0] ^ dot(2, state[i][1]) ^ dot(3, state[i][2]) ^ state[i][3];
    t[2] = state[i][0] ^ state[i][1] ^ dot(2, state[i][2]) ^ dot(3, state[i][3]);
    t[3] = dot(3, state[i][0]) ^ state[i][1] ^ state[i][2] ^ dot(2, state[i][3]);
    state[i][0] = t[0];
    state[i][1] = t[1];
    state[i][2] = t[2];
    state[i][3] = t[3];
  }
  return 0;
}

void InvMixColumns(vector<vector<int>> &state)
{
  int i;
  vector<int> t(4);

  for (i = 0; i < 4; i++)
  {
    t[0] = dot(0xe, state[i][0]) ^ dot(0xb, state[i][1]) ^ dot(0xd, state[i][2]) ^ dot(0x9, state[i][3]);
    t[1] = dot(0x9, state[i][0]) ^ dot(0xe, state[i][1]) ^ dot(0xb, state[i][2]) ^ dot(0xd, state[i][3]);
    t[2] = dot(0xd, state[i][0]) ^ dot(0x9, state[i][1]) ^ dot(0xe, state[i][2]) ^ dot(0xb, state[i][3]);
    t[3] = dot(0xb, state[i][0]) ^ dot(0xd, state[i][1]) ^ dot(0x9, state[i][2]) ^ dot(0xe, state[i][3]);
    state[i][0] = t[0];
    state[i][1] = t[1];
    state[i][2] = t[2];
    state[i][3] = t[3];
  }
}
int RotWord(vector<int> &word)
{
  rotate(word.begin(), word.begin() + 1, word.end());
  return 0;
}

int SubWord(vector<int> &word)
{
  int k, l;
  for (int i = 0; i < nb; i++)
  {
    k = word[i] / 16;
    l = word[i] % 16;
    word[i] = Sbox[k][l];
  }
  return 0;
}
int XorWord(vector<int> &x, vector<int> &y)
{
  int j;
  for (j = 0; j < 4; j++)
  {
    x[j] = x[j] ^ y[j];
  }
  return true;
}
// KeyExpansion関数：新たな暗号化鍵生成を行う
int KeyExpansion(vector<vector<int>> &key, int i)
{
  int j, l, m;
  vector<int> word0(4);
  vector<int> word1(4);
  vector<int> word2(4);
  vector<int> word3(4);
  vector<int> word(4);
  for (j = 0; j < 4; j++)
  {
    word0[j] = key[0][j];
    word1[j] = key[1][j];
    word2[j] = key[2][j];
    word3[j] = key[3][j];
    word[j] = key[3][j];
  }

  int k;

  vector<int> RC = {
      0x00,
      0x01,
      0x02,
      0x04,
      0x08,
      0x10,
      0x20,
      0x40,
      0x80,
      0x1b,
      0x36};
  vector<int> Rcon(4);
  Rcon[1] = 0;
  Rcon[2] = 0;
  Rcon[3] = 0;

  Rcon[0] = RC[i];
  RotWord(word);
  SubWord(word);
  XorWord(word, Rcon);
  XorWord(word0, word);
  XorWord(word1, word0);
  XorWord(word2, word1);
  XorWord(word3, word2);
  for (k = 0; k < 4; k++)
  {
    word[k] = word3[k];
  }

  for (l = 0; l < 4; l++)
  {
    key[0][l] = word0[l];
    key[1][l] = word1[l];
    key[2][l] = word2[l];
    key[3][l] = word3[l];
  }
  return 0;
}
int InvKeyExpansion(vector<vector<int>> &decryptionKey, int i)
{
  int j, l, m;
  vector<int> word0(4);
  vector<int> word1(4);
  vector<int> word2(4);
  vector<int> word3(4);
  vector<int> word(4);
  for (j = 0; j < 4; j++)
  {
    word0[j] = decryptionKey[0][j];
    word1[j] = decryptionKey[1][j];
    word2[j] = decryptionKey[2][j];
    word3[j] = decryptionKey[3][j];
    word[j] = decryptionKey[3][j];
  }

  int k;

  vector<int> RC = {
      0x00,
      0x01,
      0x02,
      0x04,
      0x08,
      0x10,
      0x20,
      0x40,
      0x80,
      0x1b,
      0x36};
  vector<int> Rcon(4);
  Rcon[1] = 0;
  Rcon[2] = 0;
  Rcon[3] = 0;

  Rcon[0] = RC[i];
  XorWord(word3, word2);
  XorWord(word2, word1);
  XorWord(word1, word0);
  for (k = 0; k < 4; k++)
  {
    word[k] = word3[k];
  }
  RotWord(word);
  SubWord(word);
  XorWord(word, Rcon);
  XorWord(word0, word);

  for (l = 0; l < 4; l++)
  {
    decryptionKey[0][l] = word0[l];
    decryptionKey[1][l] = word1[l];
    decryptionKey[2][l] = word2[l];
    decryptionKey[3][l] = word3[l];
  }
  return 0;
}

// show関数：現在の状態を表示
int show(vector<vector<int>> &state)
{
  int i, j, StartOfRound, RoundKeyValue;
  for (j = 0; j < 4; j++)
  {
    for (i = 0; i < 4; i++)
    {
      StartOfRound = state[i][j];  // 元の配列の縦一列を横一列に持ってくる
      cout << hex << StartOfRound; // state[縦を捜査][横を捜査]
      cout << " ";
    }
    cout << endl;
  }
  printf("\n");
  return 0;
}
// Chipher関数：11回回して暗号化する
int Encryption(vector<vector<int>> &state, vector<vector<int>> &key)
{
  int i;
  for (i = 1; i < 10; i++)
  {
    AddRoundKey(state, key);
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    KeyExpansion(key, i);
  }
  AddRoundKey(state, key);
  SubBytes(state);
  ShiftRows(state);
  KeyExpansion(key, 10);
  AddRoundKey(state, key);
  show(state);
  return 0;
}

int Decryption(vector<vector<int>> &encryptionState, vector<vector<int>> &decryptionKey)
{
  printf("復号化\n");
  show(encryptionState);
  show(decryptionKey);
  InvAddRoundKey(encryptionState, decryptionKey);
  InvKeyExpansion(decryptionKey, 10);
  InvShiftRows(encryptionState);
  InvSubBytes(encryptionState);

  for (int i = 9; i >= 1; i--)
  {
    InvAddRoundKey(encryptionState, decryptionKey);
    InvKeyExpansion(decryptionKey, i);
    InvMixColumns(encryptionState);
    InvShiftRows(encryptionState);
    InvSubBytes(encryptionState);
  }
  InvAddRoundKey(encryptionState, decryptionKey);
  show(encryptionState);
  show(decryptionKey);
  return 0;
}

int main(void)
{
  show(state);
  show(key);
  Encryption(state, key);
  show(state);
  show(key);
  int i, j;
  vector<vector<int>> encryptionState(4, vector<int>(4));
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      encryptionState.at(j).at(i) = state[j][i];
    }
  }
  vector<vector<int>> decryptionKey(4, vector<int>(4));
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      decryptionKey.at(j).at(i) = key[j][i];
    }
  }
  Decryption(encryptionState, decryptionKey);
  show(encryptionState);
  show(decryptionKey);
}
