
void sortReports(){
    sort(ar.begin(), ar.end(), [](const AnomalyReport& lhs, const AnomalyReport& rhs) {

        if (lhs.description == rhs.description)
            return lhs.timeStep > rhs.timeStep;

        return  lhs.description > rhs.description;
    });
};

vector<pair<int,int>> reportVector(){
    int startTime, currentTime;
    vector<pair<int,int>> reportVec;

    sortReports();
    startTime = ar.begin()->timeStep;
    currentTime = startTime;

    for(const auto& report : ar){
        if (report.timeStep != currentTime + 1){
            pair<int,int> tempPair(startTime,currentTime);
            reportVec.push_back(tempPair);
            startTime = report.timeStep;
            currentTime = startTime;
        }
        else
            currentTime = report.timeStep;
    }
    return reportVec;
}