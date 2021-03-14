import React from "react";
import { useStyles } from "./styles";

export const LoadingContent: React.FC = () => {
  const classes = useStyles();

  return <div className={classes.container}>loading...</div>;
};
