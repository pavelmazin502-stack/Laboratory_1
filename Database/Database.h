#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <map>

#include "../h.files/Array.h"
#include "../h.files/SinglyList.h"
#include "../h.files/DoublyList.h"
#include "../h.files/Stack.h"
#include "../h.files/Queue.h"
#include "../h.files/CompleteTree.h"

enum class Command {
    // Массив (M)
    MPUSH, MGET, MDEL, MSET, MINSERT, MLEN,

    // Односвязный список (F)
    FPUSH, FPUSH_HEAD, FPUSH_TAIL, FDEL, FPOP_HEAD, FPOP_TAIL,
    FDEL_VAL, FFIND, FGET, FINSERT_BEFORE, FINSERT_AFTER,

    // Двусвязный список (L)
    LPUSH, LPUSH_HEAD, LPUSH_TAIL, LDEL, LPOP_HEAD, LPOP_TAIL,
    LDEL_VAL, LFIND, LGET, LINSERT_BEFORE, LINSERT_AFTER,

    // Стек (S)
    SPUSH, SPOP, SPEEK,

    // Очередь (Q)
    QPUSH, QPOP, QPEEK,

    // Complete Binary Tree (T)
    TINSERT, TFIND, TISCOMPLETE, TGET,

    // Универсальные команды
    PRINT, ISMEMBER,

    // Неизвестная команда
    UNKNOWN
};

struct Database {
    std::map<std::string, MyArray> arrays;
    std::map<std::string, SinglyList> slists;
    std::map<std::string, DoublyList> dlists;
    std::map<std::string, Stack> stacks;
    std::map<std::string, Queue> queues;
    std::map<std::string, CompleteTree> trees;

    void load(const std::string& filename);
    void save(const std::string& filename);
    void execute(const std::vector<std::string>& tokens);
};

#endif 