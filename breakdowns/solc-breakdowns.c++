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

// Function dispatching for setNumberOfHorses
DUP1                    // [function selector, function selector]
PUSH4 0xcdfead2e        // [0xcdfead2e, function selector, function selector]
EQ                      // [function selector == 0xcdfead2e, function selector]
PUSH1 0x34              // [0x34, function selector == 0xcdfead2e, function selector]
JUMPI                   // [function selector]
// if function selector == 0xcdfead2e -> set_number_of_horses

// Function dispatching for readNumberOfHorses
DUP1                    // [function selector, function selector]                
PUSH4 0xe026c017        // [0xe026c017, function selector, function selector]
EQ                      // [function selector == 0xe026c017, function selector]
PUSH1 0x45              // [0x45, function selector == 0xe026c017, function selector]
JUMPI                   // [function selector]
// if function_selector == 0xe026c017 -> get_number_of_horses

// calldata_jump
// Revert Jumpdest
JUMPDEST                // []
PUSH0                   // [0x00]
DUP1                    // [0x00, 0x00]
REVERT                  // []

// updateHorseNumber jump dest 1
// setup jumping program counters in the stack
JUMPDEST                // [function selector]
PUSH1 0x43              // [0x43, function selector]
PUSH1 0x3f              // [0x3f, 0x43, function selector]
CALLDATASIZE            // [msg.data.length, 0x3f, 0x43, function selector]
PUSH1 0x04              // [0x04, msg.data.length, 0x3f, 0x43, function selector]
PUSH1 0x59              // [0x59, 0x04, msg.data.length, 0x3f, 0x43, function selector]
JUMP                    // [0x04, msg.data.length, 0x3f, 0x43, function selector]

// Jump dest 4
// We can finally run an sstore to save our value to storage:
// 1. Function dispatch
// 2. Checked for msg.value
// 3. Checked that calldata is long enough
// 4. Received the number to use from the calldata
JUMPDEST                // [calldata of numberToUpdate, 0x43, function selector]
PUSH0                   // [0x00, calldata of numberToUpdate, 0x43, function selector]
SSTORE                  // [0x43, function selector]
JUMP                    // [function selector]
// Jump dest 5

// Jump dest 5
JUMPDEST                // [function selector]
STOP                    // [function selector]
   
// readNumberOfHorses jump dest 1
JUMPDEST                // [function selector]
PUSH0                   // [0x00, function selector]
SLOAD                   // [numHorses, function selector]
PUSH1 0x40              // [0x40, numHorses, function selector]
MLOAD                   // [0x80, numHorses, function selector] // Memory [0x40: 0x80] (free memory pointer)
SWAP1                   // [numHorses, 0x80, function selector]
DUP2                    // [numHorses, 0x80, function selector, numHorses]
MSTORE                  // [0x80, function selector] Memory: 0x80: numHorses
PUSH1 0x20              // [0x20, 0x80, function selector]
ADD                     // [0xa0, function selector]
PUSH1 0x40              // [0x40, 0xa0, function selector]
MLOAD                   // [0x80, 0xa0, function selector]         
DUP1                    // [0x80, 0x80, 0xa0, function selector]
SWAP2                   // [0xa0, 0x80, 0x80, function selector]
SUB                     // [0x20, 0x80, function selector]
SWAP1                   // [0x80, 0x20, function selector]
// Return a value of size 32-bytes that is located at position 0x80 in memory
RETURN                  // [function selector]

// updateHorseNumber jump dest 2
// Check to see if there is a value to update the horse number to
// 4 bytes for the function selector, 32 bytes for the horse number
JUMPDEST                // [0x04, msg.data.length, 0x3f, 0x43, function selector]
PUSH0                   // [0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
PUSH1 0x20              // [0x20, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
DUP3                    // [0x04, 0x20, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
DUP5                    // [msg.data.length, 0x04, 0x20, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
SUB                     // [msg.data.length - 0x04, 0x20, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
// is there more calldata than just the function selector?
SLT                     // [msg.data.length - 0x04 < 0x20, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
ISZERO                  // [msg.data.length - 0x04 < 0x20 == true, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
PUSH1 0x68              // [0x68, msg.data.length - 0x04 < 0x20 == true, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
JUMPI                   // [0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]        
// We are goint to jump to jump dest 3 if there is more calldata than just the function selector + 0x20

// Revert if there isn't enough calldata
PUSH0                   // [0x00, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
DUP1                    // [0x00, 0x00, 0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
REVERT

// updateHorseNumber jump dest 3
// Grab the calldata for updating the horse number
// Delete some stuff in the stack
JUMPDEST                // [0x00, 0x04, msg.data.length, 0x3f, 0x43, function selector]
POP                     // [0x04, msg.data.length, 0x3f, 0x43, function selector]
CALLDATALOAD            // [calldata of numberToUpdate, msg.data.length, 0x3f, 0x43, function selector]
SWAP2                   // [0x3f, msg.data.length, calldata of numberToUpdate, 0x43, function selector]
SWAP1                   // [msg.data.length, 0x3f, calldata of numberToUpdate, 0x3f, 0x43, function selector]
POP                     // [0x3f, calldata of numberToUpdate, 0x43, function selector]
JUMP
// jump to jump dest 4

// 3. Metadata
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