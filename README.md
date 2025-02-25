![Green Cartoon Animated Memory Game Presentation](https://github.com/user-attachments/assets/19dc52d0-4c68-4fb8-8017-7a7dcb0bba18)


# Odds or Evens, a game Hook 

## Introduction

Odds or Evens is a hook programmed in C for the Xahau blockchain. A hook is a series of rules that enable smart logic in Xahau, considered the smart contracts of Xahau. 

Odds or Evens is a Hook that converts a Xahau account in an engine for a simple game. One player will hava an Odd or and Even number based on the ledger index sequence of the payment he sent. Next player will have an Odd or an Even number based on the ledger index sequence ledger of the payment he sent. 

This hook is based in the Highest Number Hook by @ekiserrepe. That hook had an undesirable thing, the range between numbers where in some cases predictable, for example, if first player had a 0 or 1, then there were high chances the second player was able to win because, 2, 3, 4, 5, 6, 7, 8 and 9 would win him. So I thought this should be reduced to a range of 2 options, this way the result would be less predictable. A way to do so is reduce the ledger sequence number to an odd or even number or to its corresponding remainders when they are divided by 2. The result of dividing the ledger index sequence by 2 is 0 for even numbers, or 1 for odd numbers.

But who wins?

If the first player has a remainder of 0 and the second player a remainder of 0, the first player wins. 

If the first player has a remainder of 0 and the second player a remainder of 1, the second player wins. 

If the first player has a remainder of 1 and the second player a remainder of 1, the first player wins. 

If the first player has a remainder of 1 and the second player a remainder of 0, the second player wins. 

These rules can be sumarized like this:
Compare the remainders of both players regarding being odd or even, if they are equal, first player wins, if they are different, second player wins.


## Explanation

**Attention:** Only use if you are sure of what you are doing on Testnet/Mainnet. You could put your funds at risk. It is recommended to install on new accounts.

The hook when installed allows you to play the game of the odds or evens numbers. The hook will accept two players sending 1 XAH. With each payment the hook will check the ledger index sequence. The hook will check if it's an odd or even number and store the remainder of the division in the namespace next to the address of the first player referring to the first payment he receives. When a second player sends a payment of 1 XAH to the hook address, the hook will check the ledger index sequence and compare the remainder with that of the first player. This can lead to 2 possible outcomes. Both have the same remainder or a different one. If both have the same remainder, Player 1 wins and receives 2 XAH. If both players have a different remainder, Player 2 wins and receives 2 XAH. 

The hook blocks any payment other than 1 XAH. So a third case could occur, that the hook account runs out of funds and the game cannot be managed. If there are insufficient funds it might not be possible to send the “prize” to the winners. Therefore, it has been enabled to manage an account known as funding “FUND” that the hook allows to operate payments in both directions to be able to take out or put in XAH and avoid the mentioned problem. To assign a “FUND” account it is necessary to create an Invoke transaction from the Hook account with the parameter “FUND” and the account that we want to assign as a “FUND” account in the parameter value. The process is explained below.


## Installation & Usage

Once the hook is installed, the following triggers are expected for the hook.

- An account will send a payment of 1 XAH to the hook account. The payment account will be known as Player 1. The hook will register in the namespace the address of Player one with the key P1AD and store the odd or even number of the ledger sequence in the namespace under the key P1LG.

- A second account (different from the first one) will send a payment of 1 XAH to the hook account. The payment account will be known as Player 2. The hook will compare the oddeness or eveness of the ledger index sequence number with that of Player 1 and decide the final result of the game.

- An Invoke transaction from the hook account with the hook parameter “FUND” and the desired address as value in HEX format. This will store in the namespace the information with the key “FUND” and with value the address in HEX.


## How to install the Odds or Evens Hook on Testnet?

HookHash: 89E9C5B8F04BD9C23AA0299573B0EBC43091AEBB5AFC90D4A353020A00CEFDE7

1. You can do it by [XRPLWin Hook Install Tool](https://xahau-testnet.xrplwin.com/tools/hook/from-hash)
   

## I want to try them without installing anything

You can try this hook just sending 1 XAH to the following account on TESTNET and wait until somebody else sends 1 XAH to it and see who wins (or you can just create a second account on testnet and send yourself 1 XAH from this different account and see who wins):

- Testnet hook account:   r9uM7PHEYvMqBQsuFzAany9xucXfrQsLDr


## Credits

This hook was originally created by @ekiserrepe. You can find more of his projects on ekiserrepe.com
