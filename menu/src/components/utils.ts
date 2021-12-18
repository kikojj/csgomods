import React from "react";

export const join = (...classes: (string | undefined | boolean)[]) =>
  classes.filter(className => className && typeof className === "string").join(" ");

export const useProvidableState = <StateType,>(
  initialState: StateType,
  state?: StateType,
  setState?: (state: StateType) => void,
): [StateType, (state: StateType) => void] => {
  const [_state, _setState] = React.useState<StateType>(initialState);

  const __state = React.useMemo(
    () => (state !== undefined && setState !== undefined ? state : _state),
    [state, _state, setState]
  );
  const __setState = React.useMemo(
    () =>
      state !== undefined && setState !== undefined ? setState : _setState,
    [state, setState, _setState]
  );

  return [__state, __setState];
};