import React from "react";
import ClickAwayListener from "react-click-away-listener";
import { SelectItem } from "@components";
import { join, useProvidableState } from "@components/utils";
import { SelectIcon } from "./images";
import { useStyles } from "./styles";

export type SelectProps = {
  className?: string;
  placeholder?: string;
  value?: string;
  onChange?: (v: string) => void;
  children:
    | React.ReactComponentElement<typeof SelectItem>
    | React.ReactComponentElement<typeof SelectItem>[];
};
export function Select({
  className,
  placeholder,
  value: _value,
  onChange: _onChange,
  children,
}: SelectProps) {
  const classes = useStyles();

  const [isShow, setShow] = React.useState<boolean>(false);
  const [value, onChange] = useProvidableState("", _value, _onChange);

  if (!Array.isArray(children)) {
    children = [children];
  }

  const valueElement = children.find((child) => child.props.value === value);

  const onPlaceholderClick = React.useCallback(
    () => !value && setShow(true),
    [value, setShow]
  );

  const onClick = React.useCallback(() => setShow(true), [setShow]);

  const onKeyDown = React.useCallback(
    (event: React.KeyboardEvent<HTMLDivElement>) => {
      if (event.key === "Enter") {
        setShow(true);
      }
    },
    [setShow]
  );

  const onSelectListClick = React.useCallback(
    (e: React.MouseEvent<HTMLDivElement, MouseEvent>) => {
      onChange((e.target as any).getAttribute("data-value"));
      setShow(false);
    },
    [onChange, setShow]
  );

  const onClickAway = React.useCallback(() => setShow(false), [setShow]);

  return (
    <div
      className={join(
        classes.selectContainer,
        value && `${classes.selectContainer}-focus`,
        className
      )}
    >
      {placeholder && (
        <div
          className={join(
            classes.placeholder,
            value && `${classes.placeholder}-value`
          )}
          onClick={onPlaceholderClick}
        >
          {placeholder}
        </div>
      )}
      <div
        className={classes.select}
        tabIndex={0}
        onClick={onClick}
        onKeyDown={onKeyDown}
      >
        <div className={classes.value}>
          {valueElement?.props.children || ""}
        </div>
        <span>
          <img src={SelectIcon} />
        </span>
      </div>
      {isShow && (
        <ClickAwayListener onClickAway={onClickAway}>
          <div className={classes.selectItemList} onClick={onSelectListClick}>
            {children}
          </div>
        </ClickAwayListener>
      )}
    </div>
  );
}
