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

type AverageProps = { data: IRadarData[] };
const Average: React.FC<AverageProps> = ({ data }) => {
  const classes = useStyles();

  const players = data.filter((p) => !p.isFakePlayer);

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

    avgMVPs = data.map((p) => p.MVPs).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;

    avgScore = data.map((p) => p.score).reduce((prevValue, currentValue) => prevValue + currentValue) / data.length;
  }

  if (players.length > 0) {
    avgRanks =
      players.map((p) => p.competitiveRanking).reduce((prevValue, currentValue) => prevValue + currentValue) /
      players.length;
    avgWins =
      players.map((p) => p.competitiveWins).reduce((prevValue, currentValue) => prevValue + currentValue) /
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
              src={avgRanks < 1 || avgRanks > 18 ? ranks.Rank_None : ranks[`Rank_${avgRanks}` as keyof typeof ranks]}
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
              {avgWins}
            </React.Fragment>
          ) : (
            ""
          )}
        </div>
      </div>
      <div className={classes.player_stats}>
        <div className={classes.player_money}>${avgMoney}</div>
        <div className={classes.player_stat}>{avgKills}</div>
        <div className={classes.player_stat}>{avgAssists}</div>
        <div className={classes.player_stat}>{avgDeaths}</div>
        <div className={classes.player_mvps}>{avgMVPs}</div>
        <div className={classes.player_stat} style={{ marginRight: 0 }}>
          {avgScore}
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
        items={[
          {
            content: <Header />,
          },
          ...Ts.map((data) => {
            return {
              content: <Player playerData={data} />,
              onClick: () => setSelectedPlayer(data.userID),
              selected: selectedPlayer === data.userID,
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
              onClick: () => setSelectedPlayer(data.userID),
              selected: selectedPlayer === data.userID,
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
