import React from "react";

import { DataContext } from "@contexts";
import { Group, List } from "@components";

import { IRadarData } from "@ts/requests";
import { ranks, TeamNum } from "@utils";

import { CupIcon, StarIcon } from "./images";
import { useStyles } from "./styles";

type PlayerProps = { playerData: IRadarData };
const Player: React.FC<PlayerProps> = ({ playerData }) => {
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

export const PlayersListContent: React.FC = () => {
  const classes = useStyles();

  const { radarData } = React.useContext(DataContext);

  const [selectedPlayer, setSelectedPlayer] = React.useState<number>(-1);

  const Ts = radarData.filter((d) => d.teamNum === TeamNum.TERRORIST).sort((d1, d2) => d2.score - d1.score);
  const CTs = radarData.filter((d) => d.teamNum === TeamNum.COUNTER_TERRORIST).sort((d1, d2) => d2.score - d1.score);

  const TList: React.FC = React.useCallback(() => {
    return (
      <List
        items={Ts.map((data) => {
          return {
            content: <Player playerData={data} />,
            onClick: () => setSelectedPlayer(data.userID),
            selected: selectedPlayer === data.userID,
          };
        })}
      />
    );
  }, [Ts]);

  const CTList: React.FC = React.useCallback(() => {
    return (
      <List
        items={CTs.map((data) => {
          return {
            content: <Player playerData={data} />,
            onClick: () => setSelectedPlayer(data.userID),
            selected: selectedPlayer === data.userID,
          };
        })}
      />
    );
  }, [CTs]);

  return (
    <div>
      <div>
        <Group width="100%" label="Players list">
          <TList />
          <CTList />
        </Group>
      </div>
    </div>
  );
};
