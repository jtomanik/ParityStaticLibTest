//
//  Ethash.metal
//  EthashMetalTest
//
//  Created by Jakub Tomanik on 24/01/2019.
//  Copyright © 2019 Jakub Tomanik. All rights reserved.
//

#include <metal_stdlib>
using namespace metal;

#define ETHASH_REVISION 23
#define ETHASH_DATASET_BYTES_INIT 1073741824U // bytes in dataset at genesis 2**30
#define ETHASH_DATASET_BYTES_GROWTH 8388608U  // dataset growth per epoch 2**23
#define ETHASH_CACHE_BYTES_INIT 1073741824U // bytes in cache at genesis 2**24
#define ETHASH_CACHE_BYTES_GROWTH 131072U  // cache growth per epoch 2**17
#define ETHASH_EPOCH_LENGTH 30000U // blocks per epoch
#define ETHASH_WORD_BYTES = 4 // bytes in word, 32 bits
#define ETHASH_MIX_BYTES 128 // width of mix, 1024 bits
#define ETHASH_HASH_BYTES 64 // hash length in bytes, 512bits
#define ETHASH_DATASET_PARENTS 256 // number of parents of each dataset element
#define ETHASH_CACHE_ROUNDS 3 // number of rounds in cache production
#define ETHASH_ACCESSES 64 // number of accesses in hashimoto loop
#define ETHASH_DAG_MAGIC_NUM_SIZE 8
#define ETHASH_DAG_MAGIC_NUM 0xFEE1DEADBADDCAFE

typedef size_t uint64_t;
typedef struct ethash_h256 { uint8_t b[32]; } ethash_h256_t;

typedef ethash_block_number_t uint64_t;
typedef ethash_nonce_t uint64_t;
typedef ethash_cache_size_t uint64_t;


