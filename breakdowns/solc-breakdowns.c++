//0x6080604052
//348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea26469706673582212209a620bbeb20a2a56ec7086b5c70095e686248474ab95658191bf1faf1e293c1164736f6c63430008140033

// 1. Contract Creation Code
// Free memory pointer
PUSH1 0x80              // [0x80]
PUSH1 0x40              // [0x80, 0x40]
MSTORE                  // []            // Memory 0x40 -> 0x80

// Revert if someone sent value with this call, otherwise jump to 0x0E PC/JUMPDEST
CALLVALUE               // [msg.value]
DUP1                    // [msg.value, msg.value]
ISZERO                  // [msg.value == 0, msg.value]
PUSH1 0x0e              // [0x0E, msg.value == 0, msg.value]
JUMPI                   // [msg.value]
PUSH0                   // [0x00, msg.value]
DUP1                    // [0x00, 0x00, msg.value]
REVERT                  // [msg.value]

// Jumpdest if msg.value == 0
JUMPDEST                // [msg.value]
POP                     // []
PUSH1 0xa5              // [0xa5]
DUP1                    // [0xa5, 0xa5]
PUSH2 0x001b            // [0x001b, 0xa5, 0xa5]
PUSH0                   // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY                // [0xa5]               Memory: [runtime code]
PUSH0                   // [0x00, 0xa5]
RETURN                  // []
INVALID                 // []

// 2. Runtime Code
// Entry point of all calls
// free memory pointer
PUSH1 0x80  
PUSH1 0x40
MSTORE


CALLVALUE               // [msg.value]
DUP1                    // [msg.value, msg.value]
ISZERO                  // [msg.value == 0, msg.value]
PUSH1 0x0e              // [0x0e, msg.value == 0, msg.value]
JUMPI                   // [msg.value]
PUSH0                   // [0x00, msg.value]
DUP1                    // [0x00, 0x00, msg.value]
REVERT                  // [msg.value]

// If msg.value == 0, start here
// continue
// checking to see if there is enough calldata for a function selector
JUMPDEST                // [msg.value]
POP                     // []
PUSH1 0x04              // [0x04]
CALLDATASIZE            // [msg.data.length, 0x04]
LT                      // [msg.data.length < 0x04]
PUSH1 0x30              // [0x30, msg.data.length < 0x04]
JUMPI                   // []
// if msg.data.length < 0x04 -> calldata_jump

PUSH0                   // [0x00]
CALLDATALOAD            // [32 bytes of calldata]
PUSH1 0xe0              // [0xe0, 32 bytes of calldata]
SHR                     // [function selector]
DUP1                    // [function selector, function selector]
PUSH4 0xcdfead2e        // [0xcdfead2e, function selector, function selector]
EQ                      // [function selector == 0xcdfead2e, function selector]
PUSH1 0x34              // [0x34, function selector == 0xcdfead2e, function selector]
JUMPI                   // [function selector]
// if function selector == 0xcdfead2e -> set_number_of_horses

DUP1
PUSH4 0xe026c017
EQ
PUSH1 0x45
JUMPI

// calldata_jump
JUMPDEST                // []
PUSH0                   // [0x00]
DUP1                    // [0x00, 0x00]
REVERT                  // []

JUMPDEST
PUSH1 0x43
PUSH1 0x3f
CALLDATASIZE
PUSH1 0x04
PUSH1 0x59
JUMP
JUMPDEST
PUSH0
SSTORE
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH0
SLOAD
PUSH1 0x40
MLOAD
SWAP1
DUP2
MSTORE
PUSH1 0x20
ADD
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
DUP5
SUB
SLT
ISZERO
PUSH1 0x68
JUMPI
PUSH0
DUP1
REVERT
JUMPDEST
POP
CALLDATALOAD
SWAP2
SWAP1
POP
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
SWAP11
PUSH3 0x0bbeb2
EXP
INVALID
JUMP
INVALID
PUSH17 0x86b5c70095e686248474ab95658191bf1f
INVALID
INVALID
INVALID
EXTCODECOPY
GT
PUSH5 0x736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER