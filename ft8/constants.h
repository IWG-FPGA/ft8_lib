#ifndef _INCLUDE_CONSTANTS_H_
#define _INCLUDE_CONSTANTS_H_

#include <stdint.h>

// Define FT8 symbol counts
#define FT8_ND (58)              ///< Data symbols
#define FT8_NS (21)              ///< Sync symbols (3 @ Costas 7x7)
#define FT8_NN (FT8_NS + FT8_ND) ///< Total channel symbols (79)

// Define LDPC parameters
#define FT8_N (174)                   ///< Number of bits in the encoded message (payload + checksum)
#define FT8_K (91)                    ///< Number of payload bits
#define FT8_M (FT8_N - FT8_K)         ///< Number of LDPC checksum bits
#define FT8_N_BYTES ((FT8_N + 7) / 8) ///< Number of whole bytes needed to store N bits (full message)
#define FT8_K_BYTES ((FT8_K + 7) / 8) ///< Number of whole bytes needed to store K bits (payload only)

// Define CRC parameters
#define FT8_CRC_POLYNOMIAL ((uint16_t)0x2757u) ///< CRC-14 polynomial without the leading (MSB) 1
#define FT8_CRC_WIDTH (14)

/// Costas 7x7 tone pattern for synchronization
extern const uint8_t kFT8_Costas_pattern[7];

/// Gray code map to encode 8 symbols (tones)
extern const uint8_t kFT8_Gray_map[8];

/// Parity generator matrix for (174,91) LDPC code, stored in bitpacked format (MSB first)
extern const uint8_t kFT8_LDPC_generator[FT8_M][FT8_K_BYTES];

/// Column order (permutation) in which the bits in codeword are stored
/// (Not really used in FT8 v2 - instead the Nm, Mn and generator matrices are already permuted)
extern const uint8_t kFT8_LDPC_column_order[FT8_N];

/// LDPC(174,91) parity check matrix, containing 83 rows,
/// each row describes one parity check,
/// each number is an index into the codeword (1-origin).
/// The codeword bits mentioned in each row must xor to zero.
/// From WSJT-X's ldpc_174_91_c_reordered_parity.f90.
extern const uint8_t kFT8_LDPC_Nm[FT8_M][7];

/// Mn from WSJT-X's bpdecode174.f90. Each row corresponds to a codeword bit.
/// The numbers indicate which three parity checks (rows in Nm) refer to the codeword bit.
/// The numbers use 1 as the origin (first entry).
extern const uint8_t kFT8_LDPC_Mn[FT8_N][3];

/// Number of rows (columns in C/C++) in the array Nm.
extern const uint8_t kFT8_LDPC_num_rows[FT8_M];

#endif // _INCLUDE_CONSTANTS_H_
