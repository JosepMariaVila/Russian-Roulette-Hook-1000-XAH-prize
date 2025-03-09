![russian roulette](https://github.com/user-attachments/assets/ccff29b1-7bf6-42a7-bc6a-773fb3030fa1)

# Russian Roulette, a game Hook on the Xahau network

## Introduction

Russian Roulette is a hook programmed in C for the Xahau blockchain. A hook is a series of rules that enable smart logic in Xahau, considered the smart contracts of Xahau. 

Russian Roulette is a Hook that converts a Xahau account in an engine for a simple game. One player will hava an odd or an even number based on the ledger index sequence of the payment he sent. Next player will have an odd or an even number based on the ledger index sequence ledger of the payment he sent. 

This hook is based on my Odds or Evens Hook and the Highest Number Hook by @ekiserrepe. The result of dividing the ledger index sequence by 2 is 0 for even numbers or 1 for odd numbers, based on that the Hook determines the winner as follows.

Who wins?

If the first player has a remainder of 0 and the second player a remainder of 0, the first player wins. 

If the first player has a remainder of 0 and the second player a remainder of 1, the second player wins. 

If the first player has a remainder of 1 and the second player a remainder of 1, the first player wins. 

If the first player has a remainder of 1 and the second player a remainder of 0, the second player wins. 

These rules can be sumarized like this:
Compare the remainders of both players regarding being odd or even, if they are equal, first player wins, if they are different, second player wins.


## Explanation

**DISCLAIMER:** Only use if you are sure of what you are doing on Mainnet. You could put your funds at risk. It is recommended to install on new accounts.

The hook when installed allows you to play a Russian Roulette game. The hook will accept two players sending 500 XAH. With each payment the hook will check the ledger index sequence. The hook will check if it's an odd or even number and store the remainder of the division in the namespace next to the address of the first player referring to the first payment he receives. When a second player sends a payment of 500 XAH to the hook address, the hook will check the ledger index sequence and compare the remainder with that of the first player. This can lead to 2 possible outcomes. Both have the same remainder or a different one. If both have the same remainder, Player 1 wins and receives 1000 XAH. If both players have a different remainder, Player 2 wins and receives 1000 XAH. 

The hook blocks any payment other than 500 XAH. So a third case could occur, that the hook account runs out of funds and the game cannot be managed. If there are insufficient funds it might not be possible to send the “prize” to the winners. Therefore, it has been enabled to manage an account known as funding “FUND” that the hook allows to operate payments in both directions to be able to take out or put in XAH and avoid the mentioned problem. To assign a “FUND” account it is necessary to create an Invoke transaction from the Hook account with the parameter “FUND” and the account that we want to assign as a “FUND” account in the parameter value. The process is explained below.


## Installation & Usage

Once the hook is installed, the following triggers are expected for the hook.

- An account will send a payment of 500 XAH to the hook account. The payment account will be known as Player 1. The hook will register in the namespace the address of Player one with the key P1AD and store the odd or even number of the ledger sequence in the namespace under the key P1LG.

- A second account (different from the first one) will send a payment of 500 XAH to the hook account. The payment account will be known as Player 2. The hook will compare the oddeness or eveness of the ledger index sequence number with that of Player 1 and decide the final result of the game.

- An Invoke transaction from the hook account with the hook parameter “FUND” and the desired address as value in HEX format. This will store in the namespace the information with the key “FUND” and with value the address in HEX.


## How to install the Russian Roulette on Mainnet?

Mainnet HookHash: ...

1. You can do it using this tool:  https://xahau.xrplwin.com/tools/hook/from-hash
   

## I want to try them without installing anything

You can try this hook by sending 500 XAH to the following account on MAINNET and wait until somebody else sends 500 XAH to it and see who wins:

- Mainnet Hook account:  ... 


## Credits

This hook was originally created by @ekiserrepe. You can find more of his projects on ekiserrepe.com
