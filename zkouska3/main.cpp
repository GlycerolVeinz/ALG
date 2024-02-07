#include "Birds.h"
#include <algorithm>


void makeTupletsRecursive(Field *f, int sCount, vector<BirdSector *> currentTuple, int from) {
    if (sCount == 0) {
        cerr << "\ntuple: ";
        for (auto s : currentTuple){
            cerr << s->leftCorner.first << " " << s->leftCorner.second << "; ";
        }
        cerr << "\n";

//      test fence
//        find dimensions
        int fenceYMin = std::numeric_limits<int>::max();
        int fenceXMin = std::numeric_limits<int>::max();
        int fenceYMax = -1;
        int fenceXMax = -1;
        int sectorNodesCount = 0;

        for (auto s : currentTuple){
//            if any sector is on the edge of a field don't even bother
            if (s->leftCorner.first == 0 || s->leftCorner.second == 0 ||
            s->leftCorner.first + s->height - 1 == f->height - 1 || s->leftCorner.second + s->width - 1 == f->width - 1) {
                cerr << " invalid, on edge\n";
                return;
            }

            if (s->leftCorner.first < fenceYMin)
                fenceYMin = s->leftCorner.first - 1;

            if (s->leftCorner.second < fenceXMin)
                fenceXMin = s->leftCorner.second - 1;

            if (s->leftCorner.first + s->height - 1 > fenceYMax)
                fenceYMax = s->leftCorner.first + s->height;

            if (s->leftCorner.second + s->width - 1 > fenceXMax)
                fenceXMax = s->leftCorner.second + s->width;

            sectorNodesCount += (int) s->nodes.size();
        }
        cerr << " sectorNodesCount = " << sectorNodesCount;

//        test shape of fence (shouldn't be diagonal, and should encapsulate only birdSectors i tuple)
        Node *topL = f->getNode(std::make_pair(fenceYMin, fenceXMin));
        Node *topR = f->getNode(std::make_pair(fenceYMin, fenceXMax));
        Node *bottomL = f->getNode(std::make_pair(fenceYMax, fenceXMin));
        Node *bottomR = f->getNode(std::make_pair(fenceYMax, fenceXMax));

//        test partial summs (remember to remove corners once)
        int lColDangerSumm = bottomL->dangerSumVertical - topL->dangerSumVertical;
        int rColDangerSumm = bottomR->dangerSumVertical - topR->dangerSumVertical;
        int uRowDangerSumm = topR->dangerSumHorizontal - topL->dangerSumHorizontal;
        int dRowDangerSumm = bottomR->dangerSumHorizontal - bottomL->dangerSumHorizontal;

        int rColSectorSumm = 0;
        int dRowSectorSumm = 0;

        for (int iy = fenceYMin; iy < fenceYMax; ++iy){
            rColSectorSumm += f->getNode(std::make_pair(iy, fenceXMax))->sectorNodesSumHorizontal -
                    f->getNode(std::make_pair(iy, fenceXMin))->sectorsSumHorizontal;
        }
        for (int ix = fenceXMin; ix < fenceXMax; ++ix){
            dRowSectorSumm += f->getNode(std::make_pair(fenceYMax, ix))->sectorNodesSumVertical -
                    f->getNode(std::make_pair(fenceYMin, ix))->sectorsSumVertical;
        }

//        int rColSectorSumm = bottomR->sectorNodesSumVertical - topR->sectorNodesSumVertical;
//        int dRowSectorSumm = bottomR->sectorNodesSumHorizontal - bottomL->sectorNodesSumHorizontal;

//        testing valid num of sectors
        if ((rColSectorSumm != dRowSectorSumm) ||
        rColSectorSumm != sectorNodesCount ||
        dRowSectorSumm != sectorNodesCount) {
            cerr << " invalid, num of sectors\n";
            return;
        }

//        testing if total fence sum > results so far
        int fenceTotal = lColDangerSumm + rColDangerSumm + uRowDangerSumm + dRowDangerSumm -
                (topR->val + topL->val + bottomR->val + bottomL->val);
        cerr << " fenceTotal = " << fenceTotal << " ";

        if (fenceTotal > f->res)
            f->res = fenceTotal;

//        SUCCESS
        return;
    }

    for (int i = from; i < f->sectors.size(); ++i){
        auto sector = f->sectors.at(i);
        if (find(currentTuple.begin(), currentTuple.end(), sector) != currentTuple.end())
            continue;
        currentTuple.push_back(sector);
        makeTupletsRecursive(f, sCount - 1, currentTuple, from + 1);
        currentTuple.pop_back();
    }
}

int placeFence(Field *f){
    int sectorsInField = (int) f->sectors.size() / 2;

//    make all possible n-tuplets of sectors, where n = sectorsInField
//      -> use recursion, because n can be greater then 2
    vector<BirdSector*> tuple;

    makeTupletsRecursive(f, sectorsInField, tuple, 0);

    return f->res;
}

int main() {
    Field *f = Field::readField();
    cout << placeFence(f);
    return 0;
}
