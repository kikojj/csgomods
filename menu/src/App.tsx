import React from "react";
import { BrowserRouter, Switch, Route } from "react-router-dom";

import { Window } from "./containers";
import { Window as NewWindow } from "./newVersion/containers";

import { useGlobalStyles } from "./utils";

export const App = () => {
  useGlobalStyles();
  return (
    <BrowserRouter>
      <Switch>
        <Route path="/new">
          <NewWindow />
        </Route>
        <Route path="/">
          <Window />
        </Route>
      </Switch>
    </BrowserRouter>
  );
};
