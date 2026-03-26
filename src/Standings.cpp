#include "utils.h"

#include "Standings.h"

Standings::Standings(int nw) {
    w = nw;
    win = newwin(19, w, 0, 0);
    
    h = 19;
}

Standings::~Standings() {
    log("Deleting Standings");
    delwin(win);
}

void Standings::draw() {
    wclear(win);
    
    /*
    Title
    */
    string titleT = "STANDINGS";
    string tPad (w - titleT.length(), ' ');
    string title = titleT + tPad;
    wattron(win, WA_STANDOUT);
    mvwaddnstr(win, 0, 0, title.c_str(), w);
    wattroff(win, WA_STANDOUT);
    
    for(size_t j = 0; j < data["records"].size(); j++) {
        const auto& r = data["records"][j];
        
        int ox = int(j / 3) * 35;
        int oy = j % 3 * 6 + 1;
        
        /*
        Division title bar
        */
        string divRow =     rpad(4, divAbv(r["division"]["id"])) + 
                            rpad(7, "WL") + 
                            rpad(5, "GB") +
                            rpad(6, "WGB") +
                            rpad(4, "LRD") +
                            rpad(4, "L10W");
        mvwaddnstr(
            win, 
            oy,
            ox, 
            divRow.c_str(), 
            w
        );  
        
        for (size_t i = 0; i < r["teamRecords"].size(); i++) {
            /*
            Team info
            */
            const auto& t = r["teamRecords"][i];
            
            string tAbv = teamAbv(t["team"]["name"]);
            string tWin = to_string(t["leagueRecord"]["wins"]);
            string tLos = to_string(t["leagueRecord"]["losses"]);
            string tgb = t["gamesBack"];
            string twgb = t["wildCardGamesBack"];
            string tlr = t["leagueRank"];
            
            string l10w = "";
            for (size_t reci = 0; reci < t["records"]["splitRecords"].size(); reci++) {
                const auto& rec = t["records"]["splitRecords"][reci];
                if (rec["type"] == "lastTen") {
                    l10w = to_string(rec["wins"]);
                } 
            }
            
            string teamRow =    rpad(4, tAbv) + 
                                rpad(7, tWin + "-" + tLos) + 
                                rpad(5, tgb) +
                                rpad(6, twgb) +
                                rpad(4, tlr) +
                                rpad(4, l10w);
                                
            mvwaddnstr(
                win, 
                oy + i + 1,
                ox, 
                teamRow.c_str(),
                w
            );  
        }
    }
    wrefresh(win);
}

void Standings::update() {
    log("Fetching Standings");
    cpr::Url url = "https://statsapi.mlb.com/api/v1/standings?leagueId=103,104";
    cpr::Response resp = cpr::Get(url);
    loga("Standings Status", to_string(resp.status_code));
    //log(resp.text);
    data = Json::parse(resp.text);
}

void Standings::setPos(int ny) {
    y = ny;
    mvwin(win, y, x);
}