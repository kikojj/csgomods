import React from "react";

import { IRadarData } from "@ts/requests";
import { ranks } from "@utils";

import { CupIcon } from "./images";
import { useStyles } from "./styles";

export type AverageProps = { data: IRadarData[] };
export const Average: React.FC<AverageProps> = ({ data }) => {
  const classes = useStyles();

  const players = data.filter((p) => !p.is_fake_player);

  let avgMoney = 0;
  let avgKills = 0;
  let avgAssists = 0;
  let avgDeaths = 0;
  let avgMVPs = 0;
  let avgScore = 0;

  let avgRanks = 0;
  let avgWins = 0;

  if (data.length > 0) {
    avgMoney = data.map((p) => p.money).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;

    avgKills = data.map((p) => p.kills).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;

    avgAssists = data.map((p) => p.assists).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;

    avgDeaths = data.map((p) => p.deaths).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;

    avgMVPs = data.map((p) => p.mvps).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;

    avgScore = data.map((p) => p.score).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;
  }

  if (players.length > 0) {
    avgRanks =
      players.map((p) => p.competitive_ranking).reduce((prevValue, currentValue) => prevValue + currentValue) /
      players.length;
    avgWins =
      players.map((p) => p.competitive_wins).reduce((prevValue, currentValue) => prevValue + currentValue) /
      players.length;
  }

  return (
    <div className={classes.player}>
      <div className={classes.player_info}>
        <div className={classes.player_stat}>AVG</div>
        <div className={classes.player_name}></div>
        <div className={classes.player_rank}>
          {players.length > 0 ? (
            <img
              src={
                avgRanks < 1 || avgRanks > 18
                  ? ranks.Rank_None
                  : ranks[`Rank_${Math.round(avgRanks)}` as keyof typeof ranks]
              }
              alt=""
            />
          ) : (
            ""
          )}
        </div>
        <div className={classes.player_wins}>
          {players.length > 0 ? (
            <React.Fragment>
              <img src={CupIcon} alt="" />
              {Math.round(avgWins)}
            </React.Fragment>
          ) : (
            ""
          )}
        </div>
      </div>
      <div className={classes.player_stats}>
        <div className={classes.player_money}>${Math.round(avgMoney)}</div>
        <div className={classes.player_stat}>{Math.round(avgKills)}</div>
        <div className={classes.player_stat}>{Math.round(avgAssists)}</div>
        <div className={classes.player_stat}>{Math.round(avgDeaths)}</div>
        <div className={classes.player_mvps}>{Math.round(avgMVPs)}</div>
        <div className={classes.player_stat} style={{ marginRight: 0 }}>
          {Math.round(avgScore)}
        </div>
      </div>
    </div>
  );
};
