import React from "react";
import {
  deleteConfig,
  getConfigsList,
  loadConfig,
  saveConfig,
  selectConnected,
  useConfigSelector,
  useSocketSelector,
  selectConfigsList,
} from "@services";
import { Group, TextField, Button, List } from "@components";
import { SaveIcon, LoadIcon, DeleteIcon } from "./images";
import { useStyles } from "./styles";

export const ConfigsContent: React.FC = () => {
  const classes = useStyles();

  const connected = useSocketSelector(selectConnected);
  const configsList = useConfigSelector(selectConfigsList);

  const [newConfigName, setNewConfigName] = React.useState<string>("");
  const [selectedConfig, setSelectedConfig] = React.useState<string>("");

  React.useEffect(() => {
    if (!connected) {
      return;
    }

    getConfigsList();
  }, [connected]);

  const configsListItems = React.useMemo(
    () =>
      configsList.map((name) => ({
        content: name,
        onClick: () => setSelectedConfig(name),
        selected: selectedConfig === name,
      })),
    [configsList, selectedConfig, setSelectedConfig]
  );

  return (
    <div>
      <div>
        <Group width="100%" label="New config">
          <div className={classes.newConfig}>
            <TextField
              marginTop={0}
              marginRight={15}
              placeholder="Config name"
              value={newConfigName}
              onChange={(v) => setNewConfigName(v)}
            />
            <Button
              marginTop={3}
              onClick={() => {
                if (newConfigName !== "") {
                  saveConfig(newConfigName);
                  setNewConfigName("");
                }
              }}
            >
              <img src={SaveIcon} alt="save" />
            </Button>
          </div>
        </Group>
      </div>
      <div>
        <Group marginTop={35} width="100%" label="Configs list">
          <List items={configsListItems} />
          <div className={classes.configListBtns}>
            <div className={classes.configListBtns_left}>
              <Button
                className={classes.configListBtns_save}
                onClick={() => selectedConfig && saveConfig(selectedConfig)}
              >
                <img src={SaveIcon} alt="save" />
              </Button>
              <Button
                color="#E81A1A"
                onClick={() => selectedConfig && deleteConfig(selectedConfig)}
              >
                <img src={DeleteIcon} alt="delete" />
              </Button>
            </div>
            <Button
              onClick={() => selectedConfig && loadConfig(selectedConfig)}
            >
              <img src={LoadIcon} alt="load" />
            </Button>
          </div>
        </Group>
      </div>
    </div>
  );
};
