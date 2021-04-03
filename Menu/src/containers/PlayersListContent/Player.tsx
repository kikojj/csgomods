import React from "react";

import { IRadarData } from "@ts/requests";
import { ranks } from "@utils";

import { CupIcon, StarIcon } from "./images";
import { useStyles } from "./styles";

export type PlayerProps = { playerData: IRadarData };
export const Player: React.FC<PlayerProps> = ({ playerData }) => {
  const classes = useStyles();

  return (
    <div className={classes.player}>
      <div className={classes.player_info}>
        <div className={classes.player_stat}>{playerData.is_fake_player ? "BOT" : playerData.ping}</div>
        <div className={classes.player_name}>{`${playerData.is_fake_player ? "BOT " : ""}${playerData.name}`}</div>
        <div className={classes.player_rank}>
          {playerData.is_fake_player ? (
            ""
          ) : (
            <img
              src={
                playerData.competitive_ranking < 1 || playerData.competitive_ranking > 18
                  ? ranks.Rank_None
                  : ranks[`Rank_${playerData.competitive_ranking}` as keyof typeof ranks]
              }
              alt=""
            />
          )}
        </div>
        <div className={classes.player_wins}>
          {playerData.is_fake_player ? (
            ""
          ) : (
            <React.Fragment>
              <img src={CupIcon} alt="" />
              {playerData.competitive_wins < 0 || playerData.competitive_wins > 100000
                ? 0
                : playerData.competitive_wins}
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
          <span>{playerData.mvps}</span>
        </div>
        <div className={classes.player_stat} style={{ marginRight: 0 }}>
          {playerData.score}
        </div>
      </div>
    </div>
  );
};
