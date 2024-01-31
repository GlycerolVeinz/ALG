#include "frog.h"

void solve(){
    Field *f = readField();

    Coord start = std::make_pair(f->height - 1, 0);
    Coord end = std::make_pair(0, f->length - 1);

    Node *startNode = f->getNode(start, RIGHT_DIR_NUM);
    startNode->minPathLen = 0;
    Jump first = newJump(startNode, start, RIGHT_DIR_NUM, 0);
    Frog *frog = new Frog(f, start, end);

    auto *q = new std::queue<Jump>;
    q->push(first);

    while (!q->empty()){
        Jump jump = q->front();
        q->pop();

//        check if jump is valid
        if (!frog->isValidJump(jump)){
            continue;
        }

        Node *currentNode = f->getNode(jump.to, jump.direction);

        if ( !currentNode )
            continue;
        if (currentNode->visited)
            continue;

//        std::cerr << jump.from->coord.first << " " << jump.from->coord.second << " -> " << jump.to.first << " " << jump.to.second << "\n";

        currentNode->visited = true;
        currentNode->minPathLen = currentNode->minPathLen < (jump.from->minPathLen + 1) ?
                                  currentNode->minPathLen :
                                  jump.from->minPathLen + 1;

//        END CONDITION
        if (areEqualCords(currentNode->coord, frog->end)) {
            cout << currentNode->minPathLen;
            f->res = currentNode->minPathLen;
            break;
        }

        frog->addDestinations(q, currentNode, jump);
    }
}

int main() {
    solve();
    return 0;
}
