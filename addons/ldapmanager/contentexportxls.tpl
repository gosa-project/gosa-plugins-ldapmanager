{if $LDIFError != FALSE || $type == FALSE}
<p style="margin-top:5px;">
  {t}The XLS export plugin provides methods to download a complete snapshot of the running LDAP directory as xls. You may save these files for documentation.{/t}
</p>
<hr>

<table summary="" style="width:100%;">
<tr>
	<td width="30%">
		<LABEL for="single" >{t}Export single entry{/t}</LABEL>
	</td>
	<td>
		{*<input id="text" type="text" value="" name="single">*}
		<select id="single" name="single" size="1" title="{t}Choose the data you want to Export{/t}">
			{html_options options=$choicelist selected=0}
		</select>
	</td>
	<td>
		<button type='submit' name='sfrmgetsingle'>{t}Export{/t}</button>

	</td>
</tr>
<tr>
	<td width="30%">
		<LABEL for="selfull">{t}Export complete XLS for{/t}</LABEL>
	</td>
	<td>
		<select id="selfull" name="selfull" size="1" title="{t}Choose the department you want to Export{/t}">
			{html_options options=$deplist selected=0}
		</select>
	</td>
	<td>
		<button type='submit' name='sfrmgetfull'>{t}Export{/t}</button>

	</td>
</tr>
	
{if $govmode eq "true"}
<tr>
	<td width="30%">
		<LABEL for="selivbb">{t}Export IVBB LDIF for{/t}</LABEL>
	</td>
	<td>
		<select id="selivbb" name="selivbb" size="1" title="{t}Choose the department you want to Export{/t}">
			{html_options options=$deplist selected=$depselectivbb}
		</select>
	</td>
	<td>
		<button type='submit' name='sfrmgetivbb'>{t}Export{/t}</button>

	</td>
</tr>
{/if}
</table> 


{else}


<br>
	<h1>{t}Export successful{/t}</h1>
<br>
	<div>
		<img alt="" border="0" align=middle src="images/filesaveas.png">
		<a href = "plugins/ldapmanager/getxls.php{$para}" title="{t}Click here to save the complete LDAP database to a xls file{/t} ">{t}Click here to save the LDAP Export to a xls file{/t}</a>


		<br>
		<br>
	</div>
	<div align="right">
		<button type='submit' name='back'>{msgPool type=backButton}</button>

	</div>
{/if}

<hr>

<input type="hidden" name="ignore">
