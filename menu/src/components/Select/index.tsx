import React from "react";
import ClickAwayListener from "react-click-away-listener";

import { SelectItem } from "@components";

import { join } from "../utils";

import SelectIcon from "./images/SelectIcon.svg";
import { useStyles } from "./styles";

export type SelectProps = {
  className?: string;
  placeholder?: string;
  value?: string;
  onChange?: (v: string) => void;
  children: React.ReactComponentElement<typeof SelectItem> | React.ReactComponentElement<typeof SelectItem>[];
};
export function Select({ className, placeholder, value: _value, onChange: _onChange, children }: SelectProps) {
  const classes = useStyles();
  const [isShow, setShow] = React.useState<boolean>(false);
  const [__value, __onChange] = React.useState<string>("");

  const value = _value !== undefined && _onChange !== undefined ? _value : __value;
  const onChange = _value !== undefined && _onChange !== undefined ? _onChange : __onChange;

  function clickHandler(e: React.MouseEvent<HTMLDivElement, MouseEvent>) {
    onChange((e.target as any).getAttribute("data-value"));
    setShow(false);
  }

  if (!Array.isArray(children)) {
    children = [children];
  }

  const valueEl = children.find((child) => child.props.value === value);

  return (
    <div
      className={
        classes.selectContainer +
        (value ? ` ${classes.selectContainer}-focus` : "") +
        (className ? ` ${className}` : "")
      }
    >
      {placeholder ? (
        <div
          className={join(classes.placeholder, value ? `${classes.placeholder}-value` : undefined)}
          onClick={() => !value && setShow(true)}
        >
          {placeholder}
        </div>
      ) : (
        ""
      )}
      <div
        className={classes.select}
        tabIndex={0}
        onClick={() => setShow(true)}
        onKeyDown={(e) => {
          if (e.key === "Enter") {
            setShow(true);
          }
        }}
      >
        <div className={classes.value}>{valueEl?.props.children || ""}</div>
        <span>
          <img src={SelectIcon} />
        </span>
      </div>
      {isShow && (
        <ClickAwayListener onClickAway={() => setShow(false)}>
          <div className={classes.selectItemList} onClick={clickHandler}>
            {children}
          </div>
        </ClickAwayListener>
      )}
    </div>
  );
}
