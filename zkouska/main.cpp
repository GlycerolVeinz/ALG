#include "frog.h"

void solve(){
    Field *f = readField();

    Coord start = std::make_pair(f->height - 1, 0);
    Coord end = std::make_pair(0, f->length - 1);

    Node *startNode = f->getNode(start, UP_DIR_NUM);
    startNode->minPathLen = 0;
    Jump first = newJump(startNode, start, UP_DIR_NUM, 0, false);
    Frog *frog = new Frog(f, start, end);

    auto *q = new std::queue<Jump>;
    q->push(first);

//    ALGORITHM ========================================================================================================
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
        if (currentNode->visited || currentNode->height != 0)
            continue;


//        debugging
        cerr << jump.wasSpeed << ":\n";
        cerr << jump.from->coord.first << " " << jump.from->coord.second << " -> " << jump.to.first << " " << jump.to.second << "\n";


        currentNode->visited = true;
        currentNode->minPathLen = currentNode->minPathLen < (jump.from->minPathLen + 1) ?
                                  currentNode->minPathLen :
                                  jump.from->minPathLen + 1;

        jump.wasSpeed = jump.changedDir ? jump.wasSpeed + 1 : jump.wasSpeed;
        currentNode->path = jump.from->path;
        currentNode->path.push_back(jump.to);

//        END CONDITION
        if (areEqualCords(currentNode->coord, frog->end)) {
            cout << jump.pathLen;

            cerr << "Path Length: " << currentNode->minPathLen << "\n";
            cerr << "Path: ";
            for (const Coord &step : currentNode->path) {
                cerr << "(" << step.first << ", " << step.second << ") -> ";
            }
            cerr << "(" << frog->end.first << ", " << frog->end.second << ")\n";
            break;
        }

        frog->addDestinations(q, currentNode, jump);
    }

//    print whole field
//    for (auto dir : {0,1,2,3}) {
//        cerr << "\n\n" << dir << "\n";
//        for (const auto &row: f->map[dir]) {
//            for (auto node: row) {
//                if (node->height > 0) {
//                    cerr << node->height << " ";
//                } else if (node->visited) {
//                    cerr << "X ";
//                } else {
//                    cerr << "0 ";
//                }
//            }
//            cerr << "\n";
//        }
//    }
}


int main() {
    solve();
    return 0;
}
