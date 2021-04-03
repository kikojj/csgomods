import React from "react";

import { DataContext } from "@contexts";
import { Group, List } from "@components";
import { Player } from "./Player";
import { Average } from "./Average";

import { TeamNum } from "@utils";

import { useStyles } from "./styles";

const Header: React.FC = () => {
  const classes = useStyles();
  return (
    <div className={classes.player} style={{ fontSize: 12 }}>
      <div className={classes.player_info}>
        <div className={classes.player_stat}>Ping</div>
        <div className={classes.player_name}>Name</div>
        <div className={classes.player_rank}>Rank</div>
        <div className={classes.player_wins}>Wins</div>
      </div>
      <div className={classes.player_stats}>
        <div className={classes.player_money}>Money</div>
        <div className={classes.player_stat}>K</div>
        <div className={classes.player_stat}>A</div>
        <div className={classes.player_stat}>D</div>
        <div className={classes.player_mvps}>MVP</div>
        <div className={classes.player_stat} style={{ marginRight: 0 }}>
          S
        </div>
      </div>
    </div>
  );
};

export const PlayersListContent: React.FC = () => {
  const classes = useStyles();

  const { radarData } = React.useContext(DataContext);

  const [selectedPlayer, setSelectedPlayer] = React.useState<number>(-1);

  const Ts = radarData.filter((d) => d.team_num === TeamNum.TERRORIST).sort((d1, d2) => d2.score - d1.score);
  const CTs = radarData.filter((d) => d.team_num === TeamNum.COUNTER_TERRORIST).sort((d1, d2) => d2.score - d1.score);

  const TList: React.FC = React.useCallback(() => {
    return (
      <List
        items={[
          {
            content: <Header />,
          },
          ...Ts.map((data) => {
            return {
              content: <Player playerData={data} />,
              onClick: () => setSelectedPlayer(data.user_id),
              selected: selectedPlayer === data.user_id,
            };
          }),
          {
            content: <Average data={Ts} />,
          },
        ]}
      />
    );
  }, [Ts]);

  const CTList: React.FC = React.useCallback(() => {
    return (
      <List
        items={[
          {
            content: <Header />,
          },
          ...CTs.map((data) => {
            return {
              content: <Player playerData={data} />,
              onClick: () => setSelectedPlayer(data.user_id),
              selected: selectedPlayer === data.user_id,
            };
          }),
          {
            content: <Average data={CTs} />,
          },
        ]}
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
