import React from "react";

import { Button, CircularProgress } from "@material-ui/core";
import { WindowContent } from "@containers/Window/Content";
import { useStyles } from "./styles";

export const LoadingContent = () => {
  const classes = useStyles();
  return (
    <WindowContent className={classes.windowContent}>
      <CircularProgress />
      <Button className={classes.btn_reload} variant="contained" color="primary" onClick={() => location.reload()}>
        Reload page
      </Button>
    </WindowContent>
  );
};
