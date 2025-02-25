#include "hookapi.h"

int64_t hook(uint32_t reserved ) {

    // Create a reserve for 2 outgoing transactions
    etxn_reserve(2);

    // Check hook account
    unsigned char hook_accid[20];
    hook_account((uint32_t)hook_accid, 20);

    // Check the sender of the initial txn
    uint8_t acc_id[20];
    otxn_field(SBUF(acc_id), sfAccount);

    // Check destination of the initial txn
    uint8_t account_field[20];
    int32_t account_field_len = otxn_field(SBUF(account_field), sfDestination);

    // Checking if hook_accid and account_field are the same
    int equal = 0;
    BUFFER_EQUAL(equal, hook_accid, account_field, 20);

    // To know the txn type
    int64_t tt = otxn_type();

    // Fetch the sent Amount
    // Amounts can be 384 bits or 64 bits. If the Amount is an XAH value it will be 64 bits.
    unsigned char amount_buffer[48];
    int64_t amount_len = otxn_field(SBUF(amount_buffer), sfAmount);
    int64_t drops_sent = 0; // this will be the default

    // Hook params
    uint8_t fund_param[4] = {'F', 'U', 'N', 'D'};
    uint8_t p1ledger_param[4] = {'P', '1', 'L', 'G'};
    uint8_t p1address_param[4] = {'P', '1', 'A', 'D'};
    uint8_t p2ledger_param[4] = {'P', '2', 'L', 'G'};
    uint8_t p2address_param[4] = {'P', '2', 'A', 'D'};

    uint8_t p1address_ns[20] = {0x00U};
    uint8_t p2address_ns[20] = {0x00U};
    uint8_t fundaddress_ns[20] = {0x00U};
    uint8_t fundaddress_hp[20] = {0x00U};

    // Get FUND Address from namespace
    state(SVAR(fundaddress_ns), fund_param, 4);

    // Check if fundaddress is the origin payment account or the destination
    int sender_equal = 0;
    int destination_equal = 0;

    BUFFER_EQUAL(sender_equal, acc_id, fundaddress_ns, 20);
    BUFFER_EQUAL(destination_equal, account_field, fundaddress_ns, 20);

    // Check namespace's addresses
    state(SVAR(p1address_ns), p1address_param, 4);
    state(SVAR(p2address_ns), p2address_param, 4);

    // Check if the second player and first player are the same
    int players_equal = 0;
    BUFFER_EQUAL(players_equal, p1address_ns, acc_id, 20);

    // Get ledger sequence
    int64_t Ledger_Index_Sequence = ledger_seq();
    TRACEVAR(Ledger_Index_Sequence);
    // uint8_t last_digit = seq % 10;

    // Get the remainder of (seq % 2)
    uint8_t Remainder = Ledger_Index_Sequence % 2;
    TRACEVAR(Remainder);

    // Get first player remainder if exists
    uint64_t p1_digit;
    state(SVAR(p1_digit), p1ledger_param, 4);

    // If i want to add the funding account
    if (!equal && otxn_param(fundaddress_hp, 20, SBUF(fund_param))==20 && tt==99) {
        state_set(SBUF(fundaddress_hp), fund_param, 4);
        accept(SBUF("Odd or Even: Adding fund account."), 1);
    }
    // I want to allow the fund account send payments and receiving from hook account
    if (tt==00 && (sender_equal || destination_equal)) {
        accept(SBUF("Odd or Even: Funding account payment."), 2);
    }
    // If It's not XAH (other tokens). or a transaction without amount
    if (amount_len != 8){
        rollback(SBUF("Odd or Even: Not accepting IOUs or transaction type."), 3);
        }
    else // If it's XAH
    {
        int64_t otxn_drops = AMOUNT_TO_DROPS(amount_buffer);    
        drops_sent = (int64_t)((double)otxn_drops);
    }

    // If first player payment goes right, to check that, you need an incoming payment from another account (equal=1), it has to be a payment (tt==00), the amount has to be 10 XAH (drops_sent==10000000) and be the first player to enter to the game, no previous records of player in the namespace (state(SVAR(p1address_ns), p1address_param, 4) != 20)
    if (equal && state(SVAR(p1address_ns), p1address_param, 4) != 20 && tt==00 && drops_sent==10000000) {
        state_set(SVAR(Remainder), p1ledger_param, 4);
        state_set(SBUF(acc_id), p1address_param, 4);
        accept(SBUF("Odd or Even: Saving first player."), 4);
    }
    // I check if there is a second payment from different account than first player (!players_equal), its a payment tt==00 and 10 XAH drops_sent==10000000
    if (equal && state(SVAR(p1address_ns), p1address_param, 4) == 20 && !players_equal && tt==00 && drops_sent==10000000) {
        unsigned char tx01[PREPARE_PAYMENT_SIMPLE_SIZE];

        // If P2 Wins, we send 20 XAH to P2
        if((Remainder == 0) && (p1_digit != 0)){
            PREPARE_PAYMENT_SIMPLE(tx01, drops_sent*2, acc_id, 0, 0);
            uint8_t emithash01[32];
            int64_t emit_result01 = emit(SBUF(emithash01), SBUF(tx01));
        }
          if((Remainder != 0) && (p1_digit == 0)){
            PREPARE_PAYMENT_SIMPLE(tx01, drops_sent*2, acc_id, 0, 0);
            uint8_t emithash01[32];
            int64_t emit_result01 = emit(SBUF(emithash01), SBUF(tx01));
        }
        // If P1 Wins we send 20 XAH to P1
        if((Remainder == 0) && (p1_digit == 0)){
            PREPARE_PAYMENT_SIMPLE(tx01, drops_sent*2, p1address_ns, 0, 0);
            uint8_t emithash01[32];
            int64_t emit_result01 = emit(SBUF(emithash01), SBUF(tx01));
        }
         if((Remainder != 0) && (p1_digit != 0)){
            PREPARE_PAYMENT_SIMPLE(tx01, drops_sent*2, p1address_ns, 0, 0);
            uint8_t emithash01[32];
            int64_t emit_result01 = emit(SBUF(emithash01), SBUF(tx01));
        }
        
        // Deleting P1 values from namespace
        state_set(0,0, p1ledger_param, 4);
        state_set(0,0, p1address_param, 4);
        accept(SBUF("Odd or Even: We have a winner, end of the game!"), 3);
    }

    rollback(SBUF("Odd or Even: Not accepting this transaction."), 5);
    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
