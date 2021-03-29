import React from "react";

import { IRadarData } from "@ts/requests";
import { ranks } from "@utils";

import { CupIcon, StarIcon } from "./images";
import { useStyles } from "./styles";

export type PlayerProps = { playerData: IRadarData };
export const Player: React.FC<PlayerProps> = ({ playerData }) => {
  const classes = useStyles();

  return (
    <div
      className={classes.player}
      onContextMenu={(e) => {
        e.preventDefault();
        console.log("context");
      }}
    >
      <div className={classes.player_info}>
        <div className={classes.player_stat}>{playerData.isFakePlayer ? "BOT" : playerData.ping}</div>
        <div className={classes.player_name}>{`${playerData.isFakePlayer ? "BOT " : ""}${playerData.name}`}</div>
        <div className={classes.player_rank}>
          {playerData.isFakePlayer ? (
            ""
          ) : (
            <img
              src={
                playerData.competitiveRanking < 1 || playerData.competitiveRanking > 18
                  ? ranks.Rank_None
                  : ranks[`Rank_${playerData.competitiveRanking}` as keyof typeof ranks]
              }
              alt=""
            />
          )}
        </div>
        <div className={classes.player_wins}>
          {playerData.isFakePlayer ? (
            ""
          ) : (
            <React.Fragment>
              <img src={CupIcon} alt="" />
              {playerData.competitiveWins < 0 || playerData.competitiveWins > 100000 ? 0 : playerData.competitiveWins}
            </React.Fragment>
          )}
        </div>
      </div>
      <div className={classes.player_stats}>
        <div className={classes.player_money}>${playerData.money}</div>
        <div className={classes.player_stat}>{playerData.kills}</div>
        <div className={classes.player_stat}>{playerData.assists}</div>
        <div className={classes.player_stat}>{playerData.deaths}</div>
        <div className={classes.player_mvps}>
          <img src={StarIcon} alt="" />
          <span>{playerData.MVPs}</span>
        </div>
        <div className={classes.player_stat} style={{ marginRight: 0 }}>
          {playerData.score}
        </div>
      </div>
    </div>
  );
};
