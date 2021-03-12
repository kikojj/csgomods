import React from "react";
import { ConfigContext, SocketContext } from "../../contexts";

import { SectionTitle, Group } from "@components";
import { WindowContent } from "../Window/Content";

import { useStyles } from "./styles";
import { List, ListItem, Button, TextField } from "@material-ui/core";
import { Delete as DeleteIcon, Save as SaveIcon, GetApp as GetAppIcon } from "@material-ui/icons";

export const ConfigContent = () => {
  const classes = useStyles();
  const { connected } = React.useContext(SocketContext);
  const { configsList, getConfigsList, saveConfig, loadConfig, deleteConfig } = React.useContext(ConfigContext);

  const [selectedConfig, setSelectedConfig] = React.useState<string>("");
  const [newConfigName, setNewConfigName] = React.useState<string>("");

  React.useEffect(() => {
    if (!connected) {
      return;
    }
    getConfigsList();
  }, [connected]);

  return (
    <WindowContent>
      <SectionTitle text="Config" />
      <Group title="New config" marginTop={28}>
        <div className={classes.newConfig}>
          <TextField
            className={classes.newConfig_input}
            placeholder="Name"
            value={newConfigName}
            onChange={(e) => setNewConfigName(e.target.value)}
          />
          <Button
            variant="contained"
            color="primary"
            size="small"
            startIcon={<SaveIcon />}
            onClick={() => {
              if (newConfigName !== "") {
                saveConfig(newConfigName);
                setNewConfigName("");
              }
            }}
          >
            Save
          </Button>
        </div>
      </Group>
      <Group title="Configs list" marginTop={28}>
        <List className={classes.configsList}>
          {configsList.map((fileName, key) => (
            <ListItem
              key={key}
              button
              className={classes.configsList_item}
              selected={selectedConfig === fileName}
              onClick={() => setSelectedConfig(fileName)}
            >
              {fileName}
            </ListItem>
          ))}
        </List>
        <div className={classes.configsList_actions}>
          <div>
            <Button
              variant="contained"
              color="secondary"
              size="small"
              startIcon={<DeleteIcon />}
              onClick={() => selectedConfig && deleteConfig(selectedConfig)}
            >
              Delete
            </Button>
            <Button
              className={classes.configsList_actions_btnLoad}
              variant="contained"
              color="primary"
              size="small"
              startIcon={<GetAppIcon />}
              onClick={() => selectedConfig && loadConfig(selectedConfig)}
            >
              Load
            </Button>
          </div>
          <div>
            <Button
              variant="contained"
              color="primary"
              size="small"
              startIcon={<SaveIcon />}
              onClick={() => selectedConfig && saveConfig(selectedConfig)}
            >
              Save
            </Button>
          </div>
        </div>
      </Group>
    </WindowContent>
  );
};
